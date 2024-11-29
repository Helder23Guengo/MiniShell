/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eda-mata <eda-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:44:23 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/23 01:22:41 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp2(char *str1, char c)
{
	int	i;

	i = 0;
	if (!str1[i])
		return (1);
	while (str1[i] && str1[i] == c && str1[i] != 15)
		i++;
	if (str1[i])
		return (1);
	return (0);
}

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_strdup2(char **str)
{
	char	**res;
	int		i;

	res = malloc((countmatriz(str) + 1) * sizeof(char *));
	i = 0;
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = malloc((ft_strlen(str[i]) + 1) * sizeof(char));
		i++;
	}
	i = 0;
	while (str[i])
	{
		ft_strcpy(res[i], str[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	find_caracter(char *str, char caracter)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == caracter)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	remove_caracter(char **str, char caracter)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && find_caracter(str[i], caracter) == -1)
		{
			i++;
		}
		if (!str[i])
			return ;
		while (str[i][j] != caracter)
			j++;
		while (str[i][j] != '\0')
		{
			str[i][j] = str[i][j + 1];
			j++;
		}
	}
}
