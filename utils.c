/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:18:31 by eda-mata          #+#    #+#             */
/*   Updated: 2024/12/02 15:16:57 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_status(int status, char **res, int *i, int *j)
{
	int		k;
	char	*number;

	k = 0;
	number = ft_itoa(status);
	while (number[k])
	{
		res[(*i)][(*j)] = number[k];
		k++;
		(*j)++;
	}
	free(number);
}

int	fechamento(char *str, char c, int i)
{
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*getvar(char *str, int *i)
{
	int		j;
	char	*var;

	j = 0;
	var = malloc(ft_strlen(str) * sizeof(char));
	(*i)++;
	while (str[(*i)] && ((str[(*i)] >= 'a' && str[(*i)] <= 'z')
			|| (str[(*i)] >= 'A' && str[(*i)] <= 'Z'))
		|| str[(*i)] == '_' || ((str[(*i)] >= '0' && str[(*i)] <= '9')))
	{
		var[j] = str[(*i)];
		j++;
		(*i)++;
	}
	var[j] = '\0';
	return (var);
}

char	*find_comand(char **path, char *comand)
{
	int		i;
	char	*exec;

	i = 0;
	while (path[i])
	{
		exec = ft_join_not_space(path[i], comand);
		if (access(exec, X_OK) == 0)
		{
			return (exec);
		}
		free(exec);
		i++;
	}
	return (NULL);
}

int	verify_bin(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '/' || str[i] == '.')
	{
		if (access(str, X_OK) == -1)
			return (-1);
	}
	return (0);
}
