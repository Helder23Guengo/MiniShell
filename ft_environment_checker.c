/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:09:05 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/28 15:27:44 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand(char **res, char *str, int k, int j)
{
	int	i;

	i = 0;
	while (str[i])
	{
		res[k][j] = str[i];
		i++;
		j++;
	}
	res[k][j] = '\0';
	return (j);
}

char	*ft_join_not_space(char *str, char *c)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(ft_strlen(str) + ft_strlen(c) + 3 * sizeof(char ));
	while (str && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	while (c[j])
	{
		ret[i] = c[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*backequal(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*afterequal(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (str[i] != '\0')
		i++;
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	if (!str[i])
	{
		free(res);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		i++;
		res[j] = str[i];
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	add_var(char **argv, t_cmd *cmd)
{
	int				i[2];
	int				j;
	extern char		**environ;
	static char		*enverement[70000];

	i[0] = 0;
	i[1] = 1;
	while (environ[i[0]])
	{
		enverement[i[0]] = environ[i[0]];
		i[0]++;
	}
	enverement[i[0]] = NULL;
	j = 1;
	while (argv[i[1]])
	{
		aux_add_var(argv, enverement, i, cmd);
		++i[1];
	}
}
