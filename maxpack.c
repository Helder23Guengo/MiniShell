/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maxpack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:33:01 by hguengo           #+#    #+#             */
/*   Updated: 2024/12/02 13:38:40 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countmatriz(char **params)
{
	int	i;

	i = 0;
	if (!params[i])
		return (0);
	while (params[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	ft_sigquit(int sign)
{
	(void)sign;
	printf("\n");
}

void	ft_exit_130(int sign)
{
	(void)sign;
	exit(130);
}

int	ft_verify_next_red(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd->parm[i] && ft_strcmp2(cmd->parm[i], '<') != 0)
	{
		i++;
	}
	if (!cmd->parm[i])
		return (0);
	return (1);
}

char	*ft_get_path(t_cmd *cmd)
{
	char	**path;
	char	*bin;
	int		i;
	char	*var;

	i = 0;
	path = NULL;
	if (getenv("PATH"))
	{
		var = getenv("PATH");
		if (var[0])
		{
			path = ft_split_sep(var, ':');
			bin = find_comand(path, cmd->comand);
		}
		else
			bin = NULL;
	}
	else
		bin = NULL;
	if (path)
		free_matriz(path);
	return (bin);
}
