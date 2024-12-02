/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:37:31 by eda-mata          #+#    #+#             */
/*   Updated: 2024/12/02 13:05:33 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matriz(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

void	liberar(t_cmd *cmd)
{
	t_ft_dup	*aux2;
	t_ft_dup	*last;
	t_cmd		*aux;
	int			i;

	while (cmd)
	{
		i = 0;
		aux = cmd;
		if (cmd->ft_dup)
		{
			aux2 = cmd->ft_dup;
			while (aux2)
			{
				last = aux2;
				aux2 = aux2->next;
				free(last);
			}
		}
		cmd = cmd->next;
		free(aux->comand);
		free_matriz(aux->parm);
		free(aux);
	}
}

int	verify_pipe(char **params)
{
	int		i;

	i = 0;
	while (params[i])
	{
		if ((ft_strcmp2(params[i], '|') == 0
				&& params[i + 1] == NULL)
			|| (ft_strcmp2(params[i], '|' ) == 0
				&& ft_strlen(params[i]) > 1)
			|| ((ft_strcmp2(params[i], '<') == 0
					|| ft_strcmp2(params[i], '>') == 0)
				&& !params[i + 1])
			|| ((ft_strcmp2(params[i], '<') == 0
					|| ft_strcmp2(params[i], '>') == 0)
				&& ft_strcmp2(params[i + 1], '|') == 0))
		{
			printf("syntax error\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
