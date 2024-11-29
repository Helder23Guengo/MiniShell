/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:33:03 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/28 15:50:31 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tratar_caractere_c(char *str, int *i, char c, int *count)
{
	if (str[*i] == c && limite_red_space(str, *i, c) == 0)
	{
		(*count)++;
		pular_espacos(str, i);
	}
	return (0);
}

int	tratar_pipe_condicional(char *str, int *i, int *count)
{
	if (str[*i] && *i > 0 && str[*i - 1] != ' '
		&& str[*i] == '|' && str[*i + 1] != ' ')
	{
		(*i)++;
		(*count) += 2;
	}
	else if ((str[*i] && *i > 0 && str[*i] == '|' && str[*i + 1] != ' ')
		|| (str[*i] && *i > 0 && str[*i + 1] == ' '
			&& str[*i] == '|' && str[*i - 1] != ' ')
		|| (str[*i] && *i > 0 && str[*i + 1] != ' '
			&& str[*i] == '|' && str[*i - 1] == ' '))
	{
		(*i)++;
		(*count)++;
	}
	else if ((str[*i] && *i > 0 && str[*i + 1] == ' '
			&& str[*i] == '|' && str[*i - 1] == ' '))
		(*i)++;
	return (0);
}

int	tratar_redirecionamento(char *str, int *i, int *count, char v)
{
	if (str[*i] && *i > 0 && (str[*i - 1] == ' ' && limite_red(str, *i) == 1))
	{
		(*count)++;
		while (str[*i] && (str[*i] == v))
		{
			(*i)++;
		}
	}
	return (0);
}

int	tratar_aspas(char *str, int *i, char *asp)
{
	if (str[*i] && (str[*i] == '"' || str[*i] == 39))
	{
		*asp = str[*i];
		(*i)++;
		while (str[*i] != *asp && str[*i])
		{
			(*i)++;
		}
		if (!str[*i])
		{
			return (-1);
		}
		(*i)++;
	}
	return (0);
}

int	tratar_caractere(char *str, int *i, int *count, char v)
{
	if (str[*i] && *i == 0 && limite_red(str, *i) == 0)
	{
		while (str[*i] && (str[*i] == v))
			(*i)++;
	}
	else if (str[*i] && *i > 0 && (str[*i - 1] != ' '
			&& limite_red(str, *i) == 1))
	{
		(*count) += 2;
		while (str[*i] && (str[*i] == v))
		{
			(*i)++;
		}
	}
	else if (str[*i] && *i > 0 && (str[*i - 1] != ' '
			&& limite_red(str, *i) == 0))
	{
		(*count)++;
		while (str[*i] && (str[*i] == v))
		{
			(*i)++;
		}
	}
	return (0);
}
