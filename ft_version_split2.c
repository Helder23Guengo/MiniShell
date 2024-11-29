/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_version_split2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:46:14 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/29 16:45:42 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_write_split_sep(char *str, char c, int *i)
{
	char	**sp;

	(*i) = 0;
	sp = malloc((sep(str, c) + 2) * sizeof(char *));
	while ((*i) < sep(str, c) + 1)
		sp[(*i)++] = malloc(ft_strlen(str) + 1 * sizeof(char));
	return (sp);
}

void	ft_write_res2(char **res, int *i, char *str, int *k)
{
	if (str[i[0]] == 39 && fechamento(str, 39, i[0] + 1) == 1)
		i[0] = mini_split(&*res, k, str, i[0]);
	else if (str[i[0]] == '"' && fechamento(str, '"', i[0] + 1) == 1)
		i[0] = mini_split_expand(&*res, k, str, i);
	else
	{
		if (str[i[0]] && (str[i[0]] == '>'
				|| str[i[0]] == '<' || str[i[0]] == '|'))
			inputlimites(res, k, str, &i[0]);
		else
			ft_write_res(str, i, res, k);
		if (k[1] >= 0)
			res[k[0]][k[1]] = '\0';
	}
	if (!str[i[0]] || (str[i[0]] == ' ' || str[i[0]] == '	')
		|| (str[i[0]] == '<' || str[i[0]] == '>'
			|| str[i[0] - 1] == '<' || str[i[0] - 1] == '>'
			|| str[i[0]] == '|' || str[i[0] - 1] == '|') && k[1] >= 0)
	{
		k[0]++;
		k[1] = 0;
	}
}

void	ft_write_res1(char *str, char **res, int *k, int *i)
{
	char	*var;

	var = getvar(str, &i[0]);
	if (getenv(var) != NULL)
		k[1] = expand(&*res, getenv(var), k[0], k[1]);
	free(var);
}

void	ft_write_res4(char *str, char **res, int *k, int *i)
{
	res[k[0]][k[1]] = str[i[0]];
	if (str[i[0]])
		i[0]++;
	k[1]++;
}

void	ft_write_res(char *str, int *i, char **res, int *k)
{
	char	*var;

	while (str[i[0]] && verify_limit(str[i[0]]) == 0)
	{
		if (str[i[0]] == '$' && str[i[0] + 1] == '?')
		{
			input_status(i[1], res, &k[0], &k[1]);
			i[0] += 2;
		}
		else if (str[i[0]] && str[i[0]] == '$'
			&& str[i[0] + 1] == ' '
			|| !str[i[0] + 1] || str[i[0] + 1] == '$')
		{
			res[k[0]][k[1]++] = str[i[0]];
			i[0]++;
		}
		else if (str[i[0]] && str[i[0]] == '$')
			ft_write_res1(str, res, k, i);
		else if (verify_limit(str[i[0]]) == 0)
			ft_write_res4(str, res, k, i);
	}
}
