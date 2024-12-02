/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:37:42 by hguengo           #+#    #+#             */
/*   Updated: 2024/12/02 11:25:37 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	limite_red(char *str, int i)
{
	char	c;

	c = str[(i)];
	if (c && (c == '>' || c == '<'))
	{
		while (str[(i)] && str[(i)] == c)
		{
			(i)++;
		}
		if (str[(i)] && (str[(i)] == ' ' || str[(i)] == '	'))
			return (0);
		else if (str[(i)] && (str[(i)] == '|'))
			return (-1);
		else if (str[(i)] && (str[(i)] != ' ' || str[(i)] != '	'))
			return (1);
	}
	else
		return (2);
	return (-1);
}

int	limite_red_space(char *str, int i, char a)
{
	char	c;

	c = str[(i)];
	if (c && c == a)
	{
		while (str[(i)] && str[(i)] == c)
		{
			(i)++;
		}
		if (str[(i)])
			return (0);
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

int	verificar_pipe(char *str, int *i)
{
	if (str[*i] == '|')
		return (-1);
	return (0);
}

int	sep2(char *str, int *i, int *count, char *v)
{
	char	asp;

	if (str[(*i)] && (*i) > 0 && (str[(*i) - 1] == ' '
			&& limite_red(str, (*i)) == 1))
		sep3(str, count, i, v);
	else if (str[(*i)] && (*i) == 0 && limite_red(str, (*i)) == 0)
		sep4(str, count, i, v);
	else if (str[(*i)] && (*i) > 0 && (str[(*i) - 1] != ' '
			&& (str[(*i) - 1] != '<' && str[(*i) - 1] != '>')
			&& limite_red(str, (*i)) == 1))
		sep5(str, count, i, v);
	else if (str[(*i)] && (*i) > 0 && (str[(*i) - 1] != ' '
			&& limite_red(str, (*i)) == 0))
		sep6(str, count, i, v);
	else if (str[(*i)] && (*i) == 0 && limite_red(str, (*i)) == 1)
		sep7(str, count, i, v);
	else if (str[(*i)] && (*i) > 0 && (str[(*i) - 1] == ' ')
		&& limite_red(str, (*i)) == 0)
		sep4(str, count, i, v);
	else
		tratar_aspas(str, i, &asp);
}

int	sep(char *str, char c)
{
	int		i;
	int		count;
	char	v;

	i = 0;
	count = 0;
	pular_espacos(str, &i);
	if (str[i] == '|')
		return (-1);
	while (str[i])
	{
		tratar_caractere_c(str, &i, c, &count);
		tratar_pipe_condicional(str, &i, &count);
		if (limite_red(str, i) == -1)
			return (-1);
		sep2(str, &i, &count, &v);
		if (str[i] && str[i] != ' ' && str[i] != '>'
			&& str[i] != '<' && str[i] != '"' && str[i] != '|' && str[i] != 39
			|| (str[i] == ' ' && limite_red_space(str, i, c) != 0))
			i++;
	}
	return (count);
}
