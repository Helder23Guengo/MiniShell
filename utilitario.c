/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitario.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:55:02 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/29 13:22:39 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(char *c)
{
	int	i;

	i = 0;
	if (c[0] == '-' || c[0] == '+')
		i++;
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	verify_limit(char str)
{
	if (str && (str != ' ' && str != '"')
		&& str != 39 && str != '|'
		&& str != '<' && str != '>')
	{
		return (0);
	}
	return (1);
}

void	inputlimites(char **res, int *k, char *str, int *j)
{
	char	caracter;

	caracter = str[(*j)];
	while (str[(*j)] && str[(*j)] == caracter)
	{
		res[k[0]][k[1]] = str[(*j)];
		k[1]++;
		(*j)++;
	}
}
