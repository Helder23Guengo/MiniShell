/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:14:27 by hguengo           #+#    #+#             */
/*   Updated: 2024/12/02 14:41:11 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_status(char *status)
{
	printf("command not found: %s\n", status);
	exit(127);
}

void	wait_process(int *in_fd, t_cmd *cmd, int *fdpipe, char **environ)
{
	if (in_fd != NULL)
		close(*in_fd);
	if (cmd->next)
	{
		close(fdpipe[1]);
		intern(cmd->next, environ, &fdpipe[0]);
	}
}

void	close_pipe(int *in_fd, t_cmd *cmd, int *fdpipe)
{
	if (in_fd != NULL)
	{
		dup2(*in_fd, STDIN_FILENO);
		close(*in_fd);
	}
	if (cmd->next)
	{
		close(fdpipe[0]);
		dup2(fdpipe[1], STDOUT_FILENO);
		close(fdpipe[1]);
	}
}

int	verify_var(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] >= '0' && str[0] <= '9'
		|| !((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
		return (-1);
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')) || str[i] == '_'
		|| ((str[i] >= '0' && str[i] <= '9')))
	{
		i++;
	}
	if (str[i])
		return (-1);
	return (0);
}

int	find_var(char *var, char **envirom)
{
	int		i;
	char	*str;

	i = 0;
	while (envirom[i])
	{
		str = backequal(envirom[i]);
		if (ft_strcmp(str, var) == 0)
		{
			free(str);
			return (i);
		}
		free(str);
		i++;
	}
	if (envirom[i] == NULL)
		return (-1);
	return (i);
}
