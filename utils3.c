/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:18:10 by hguengo           #+#    #+#             */
/*   Updated: 2024/12/02 13:23:09 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		++i;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		++j;
		++i;
	}
	free(s1);
	str[i] = '\0';
	return (str);
}

int	space_aux(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	main_aux(char *cmd, char **environ, t_ft_dup **ft_dup_raiz)
{
	if (ft_verify_comand(cmd) == -1 || ft_check_comand(cmd) == -1
		|| sep(cmd, ' ') == -1)
		printf("syntax error near unexpected token\n");
	else
	{
		if (space_aux(cmd) == 0 && cmd[0])
			input_param(cmd, environ, &*ft_dup_raiz);
	}
	add_history(cmd);
}

int	ft_check_comand(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			ft_close_asp(str, &i, str[i]);
		if (!str[i])
			return (-1);
		if (str[i] && str[i] == '|')
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '	'))
				i++;
			if (!str[i] || str[i] == '|')
				return (-1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
