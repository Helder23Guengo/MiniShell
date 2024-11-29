/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eda-mata <eda-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:05:57 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/23 01:05:27 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_input(t_cmd *cmd, int *i)
{
	int	temp_fd;

	temp_fd = open(cmd->parm[(*i) + 1], O_RDONLY);
	return (temp_fd);
}

void	duplicate_temp(int temp)
{
	if (temp == -1)
		return ;
	else if (temp == 0)
		temp = open(".temp", O_RDONLY);
	if (temp == -1)
		return ;
	if (dup2(temp, STDIN_FILENO) == -1)
	{
		close(temp);
		perror("Error ! file duplicate\n");
		return ;
	}
	close(temp);
}

int	verify_argument(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->parm[i])
	{
		if ((ft_strcmp(cmd->parm[i], "<<") == 0
				|| ft_strcmp(cmd->parm[i], "<") == 0)
			&& (!cmd->parm[i + 1] || ft_strcmp2(cmd->parm[i + 1], '<') == 0
				|| ft_strcmp2(cmd->parm[i + 1], '>') == 0))
		{
			printf("syntax error near unexpected token\n");
			return (1);
		}
		else if ((ft_strcmp(cmd->parm[i], "<<") == 0
				|| ft_strcmp(cmd->parm[i], "<") == 0)
			&& cmd->parm[i + 1])
			i++;
		i++;
	}
	return (0);
}

void	aux_redirection(t_cmd *cmd, int *i, int status)
{
	int	temp_fd;
	int	save_stdin;
	int	dfd;

	temp_fd = -1;
	while (cmd->parm[(*i)] && g_sinal != 0)
	{
		if (ft_strcmp(cmd->parm[(*i)], "<<") == 0)
		{
			temp_fd = 0;
			ft_write_temp(cmd, i, status);
			(*i) += 2;
		}
		else if (ft_strcmp(cmd->parm[(*i)], "<") == 0)
		{
			temp_fd = ft_write_input(cmd, i);
			(*i) += 2;
		}
		else
			(*i)++;
	}
	duplicate_temp(temp_fd);
}

void	ft_red_hedoc(t_cmd *cmd, int status)
{
	int	i;

	i = 0;
	if (verify_argument(cmd) == 0)
	{
		g_sinal = 2;
		aux_redirection(cmd, &i, status);
		unlink(".temp");
	}
	else
		g_sinal = 0;
}
