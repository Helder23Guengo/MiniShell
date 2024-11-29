/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_version_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:59:44 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/29 16:34:23 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_var(char *str, int *i, int *status, char **sp)
{
	char	*var;

	if (str[status[0]] && str[status[0]] == '$'
		&& (str[status[0] + 1] == ' '
			|| str[status[0] + 1] == '"'))
	{
		sp[i[0]][i[1]++] = str[status[0]];
		status[0]++;
	}
	else if (str[status[0]] == '$' && str[status[0] + 1] == '?')
	{
		input_status(status[1], sp, &i[0], &i[1]);
		status[0] += 2;
	}
	if (str[status[0]] == '$')
	{
		var = getvar(str, &status[0]);
		if (getenv(var))
			i[1] = expand(&*sp, getenv(var), i[0], i[1]);
		if(var)
			free(var);
	}
}

int	mini_split_expand(char **sp, int *i, char *str, int *j)
{
	char	*var;

	j[0]++;
	if (str[j[0]] && (str[j[0]] == '>' || str[j[0]] == '<'
			|| str[j[0]] == '|') && verify_char(str, j[0], '"') == 0)
		sp[i[0]][i[1]++] = 15;
	while (str[j[0]])
	{
		ft_expand_var(str, i, j, sp);
		if (str[j[0]] == '"')
			break ;
		sp[i[0]][i[1]] = str[j[0]];
		i[1]++;
		j[0]++;
	}
	sp[i[0]][i[1]] = '\0';
	return (j[0] + 1);
}

int	mini_split(char **sp, int *i, char *str, int j)
{
	char	asp;

	j++;
	if (str[j] && (str[j] == '>' || str[j] == '<'
			|| str[j] == '|') && verify_char(str, j, 39) == 0)
		sp[i[0]][i[1]++] = 15;
	if (str[j] && (str[j] == '>' || str[j] == '<'
			|| str[j] == '|') && verify_char(str, j, 39) == 0)
		sp[i[0]][i[1]++] = 15;
	while (str[j] && str[j] != 39)
	{
		sp[i[0]][i[1]] = str[j];
		i[1]++;
		j++;
	}
	sp[i[0]][i[1]] = '\0';
	return (j + 1);
}

char	**ft_split_expand(char *str, int status)
{
	int		i[2];
	int		k[2];
	char	**res;

	i[0] = 0;
	k[0] = 0;
	k[1] = 0;
	i[1] = status;
	res = malloc((sep(str, ' ') + 2) * sizeof(char *));
	while (i[0] < (sep(str, ' ') + 1))
		res[i[0]++] = malloc((ft_strlen(str) + 1) * sizeof(char));
	i[0] = 0;
	while (str[i[0]])
	{
		while (str[i[0]] == ' ' || str[i[0]] == '	')
			i[0]++;
		if (!str[i[0]])
			break ;
		ft_write_res2(res, i, str, k);
	}
	res[k[0]] = NULL;
	return (res);
}

char	**ft_split_sep(char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**sp;

	sp = ft_write_split_sep(str, c, &i);
	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] != c && str[i])
		{
			sp[j][k] = str[i++];
			k++;
		}
		sp[j][k] = '/';
		sp[j][k + 1] = '\0';
		j++;
		if (str[i])
			i++;
	}
	sp[j] = NULL;
	return (sp);
}
