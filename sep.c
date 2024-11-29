/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:28:48 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/28 15:29:43 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep3(char *str, int *count, int *i, char *v)
{
	(*count)++;
	(*v) = str[(*i)];
	while (str[(*i)] && (str[(*i)] == (*v)))
		(*i)++;
}

void	sep4(char *str, int *count, int *i, char *v)
{
	(*v) = str[(*i)];
	while (str[(*i)] && (str[(*i)] == (*v)))
		(*i)++;
}

void	sep5(char *str, int *count, int *i, char *v)
{
	(*count) += 2;
	(*v) = str[(*i)];
	while (str[(*i)] && (str[(*i)] == (*v)))
		(*i)++;
}

void	sep6(char *str, int *count, int *i, char *v)
{
	(*count)++;
	(*v) = str[(*i)];
	while (str[(*i)] && (str[(*i)] == (*v)))
		(*i)++;
}

void	sep7(char *str, int *count, int *i, char *v)
{
	(*count)++;
	(*v) = str[(*i)];
	while (str[(*i)] && (str[(*i)] == (*v)))
		(*i)++;
}
