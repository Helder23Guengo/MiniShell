/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intern.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:33:30 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/28 15:19:01 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atualizar_status(int status)
{
	if (g_sinal == -1)
		return (130);
	return (status);
}

int	intern2(t_cmd *cmd, int *status, int *in_fd, char *bin)
{
	extern char	**environ;

	if (g_sinal != -1)
	{
		g_sinal = 1;
		(*status) += comands_extern(cmd, environ, in_fd, bin);
		if (bin)
			free(bin);
		g_sinal = 0;
	}
	(*status) = ft_atualizar_status((*status));
	return ((*status));
}

int	intern1(t_cmd *cmd, int *status, int *in_fd, char *bin)
{
	int				dfd;
	extern char		**environ;

	if (((ft_strcmp(cmd->comand, "<<") == 0
				|| ft_strcmp(cmd->comand, "<") == 0)
			|| ((ft_strcmp(cmd->comand, ">>") == 0
					|| ft_strcmp(cmd->comand, ">") == 0))) && cmd->next)
	{
		intern(cmd->next, environ, in_fd);
		return (0);
	}
	else if (((ft_strcmp(cmd->comand, "<<") == 0
				|| ft_strcmp(cmd->comand, "<") == 0)
			|| ((ft_strcmp(cmd->comand, ">>") == 0
					|| ft_strcmp(cmd->comand, ">") == 0))) && !cmd->next)
		return ((*status));
	dfd = dup(STDIN_FILENO);
	ft_red_hedoc(cmd, (*status));
	(*status) = intern2(cmd, &*status, in_fd, bin);
	dup2(dfd, STDIN_FILENO);
	return ((*status));
}

int	intern(t_cmd *cmd, char **environ, int *in_fd)
{
	static int		status;
	int				dfd;
	int				dfd1;
	char			*bin;

	bin = ft_get_path(cmd);
	if (cmd == NULL)
		return (0);
	if (comands_interns(cmd, environ, &status, in_fd) == 0)
		return (status);
	else
	{
		status = intern1(cmd, &status, in_fd, bin);
		if (cmd->next && ft_verify_next_red(cmd->next) == 1)
			intern(cmd->next, environ, NULL);
		return (status);
	}
	return (0);
}
