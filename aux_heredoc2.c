/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_heredoc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:24:29 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/29 13:18:16 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_imputstatus2(int status, int *j, char *res)
{
	int		k;
	char	*number;

	k = 0;
	number = ft_itoa(status);
	while (number[k])
	{
		res[(*j)] = number[k];
		k++;
		(*j)++;
	}
	free(number);
}

void	handle_heredoc(char *delimiter, int status)
{
	char	*line;
	int		temp_fd;

	delimiter = ft_remove_char15(delimiter);
	temp_fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
		return ;
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
		{
			g_sinal = 1;
			free(line);
			break ;
		}
		line = ft_expand_riredoc(line, status);
		write(temp_fd, line, ft_strlen2(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	free(delimiter);
	close(temp_fd);
}

void	ft_expand_riredoc_1(char *res, char *str, int *j, int *i)
{
	char	*var;

	if ((str[(*i)] && str[(*i)] == '$' && str[(*i) + 1] == ' ')
		|| ((str[(*i)] && str[(*i)] == '$'
				&& (!str[(*i) + 1])
				|| str[(*i) + 1] == '$')))
	{
		res[j[0]++] = str[(*i)];
		i++;
	}
	if (str[(*i)] == '$' && str[(*i) + 1] == '?')
	{
		ft_imputstatus2(j[1], &j[0], res);
		(*i) += 2;
	}
	if (str[(*i)] && str[(*i)] == '$')
	{
		var = getvar(str, i);
		if (getenv(var) != NULL)
			j[0] = ft_expandvar_2(getenv(var), res, j[0]);
		free(var);
	}
}

char	*ft_expand_riredoc(char *str, int status)
{
	int		i;
	int		j[2];
	char	*res;
	char	*var;

	i = 0;
	j[0] = 0;
	j[1] = status;
	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	while (str[i])
	{
		ft_expand_riredoc_1(res, str, j, &i);
		res[j[0]] = str[i];
		i++;
		j[0]++;
	}
	free(str);
	res[j[0]] = '\0';
	return (res);
}
