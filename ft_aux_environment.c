/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:59:59 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/29 16:10:10 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aux_unset(char **environ, char **param, int count, int nparam)
{
	int		i;
	char	*var;

	while ((count - 1) > 0)
	{
		i = 0;
		i = find_var(param[nparam], environ);
		if (!environ[i])
			return ;
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
		nparam++;
		count--;
	}
}

void	ft_trunc_dup(t_ft_dup	*novo, t_ft_dup *last, char *str)
{
	novo->str = str;
	novo->next = NULL;
	last->next = novo;
}

void	ft_new_dup(t_cmd *cmd, char *str)
{
	int			i;
	t_ft_dup	*aux;
	t_ft_dup	*novo;
	t_ft_dup	*last;

	i = 0;
	aux = cmd->ft_dup;
	novo = malloc(1 * sizeof(t_ft_dup));
	if (!novo)
		return ;
	if (aux == NULL)
	{
		novo->str = str;
		novo->next = NULL;
		cmd->ft_dup = novo;
		return ;
	}
	while (aux)
	{
		last = aux;
		aux = aux->next;
	}
	ft_trunc_dup(novo, last, str);
}

void	aux_add_var(char **argv, char *enverement[], int *i, t_cmd *cmd)
{
	char		*var;
	extern char	**environ;
	t_ft_dup	*pointer;
	int			fd;
	char		*ft_dup_copy;

	var = backequal(argv[i[1]]);
	if (verify_var(var) == -1)
	{
		free(var);
		printf("not a valid identifier\n");
		return ;
	}
	ft_dup_copy = ft_strdup(argv[i[1]]);
	if (find_var(var, enverement) != -1)
		atualiazar_enverement(enverement, ft_dup_copy, var);
	else
	{
		enverement[i[0]] = ft_dup_copy;
		enverement[++i[0]] = NULL;
	}
	ft_new_dup(cmd, ft_dup_copy);
	environ = enverement;
	free(var);
}
