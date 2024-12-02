/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   package.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:05:11 by hguengo           #+#    #+#             */
/*   Updated: 2024/12/02 11:43:19 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

char	*ft_strdup(char *src)
{
	int		cont;
	char	*dst;

	cont = 0;
	while (src[cont] != '\0')
		cont++;
	dst = malloc(sizeof(char) * cont + 1);
	if (dst == NULL)
		return (NULL);
	cont = 0;
	while (src[cont])
	{
		dst[cont] = src[cont];
		cont++;
	}
	dst[cont] = src[cont];
	return (dst);
}

int	verify_char(char *str, int i, char limite)
{
	char	caracter;

	caracter = str[i];
	while (str[i] == caracter)
	{
		i++;
	}
	if (str[i] == limite)
		return (0);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			count += 200;
		i++;
		count++;
	}
	return (count);
}
