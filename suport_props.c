/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suport_props.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:49:39 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/28 15:52:00 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	comands_externs1(t_cmd *cmd, int **fdpipe, pid_t pid, sig_t	si)
{
	int			status;
	extern char	**environ;

	if (ft_verify_next_red(cmd->next) == 0)
	{
		wait_process(fdpipe[1], cmd, fdpipe[0], environ);
		waitpid(pid, &status, 0);
		signal(SIGQUIT, si);
		status = WEXITSTATUS(status);
		return (status);
	}
	else
	{
		close(fdpipe[0][1]);
		wait(NULL);
		return (0);
	}
	return (0);
}

void	ft_print_export(int i, int j)
{
	extern char	**environ;
	char		*back;
	char		*last;

	while (environ[i] && j == 0)
	{
		back = backequal(environ[i]);
		last = afterequal(environ[i]);
		if (last)
			printf("declare -x %s=\"%s\"\n", back, last);
		else
			printf("declare -x %s\n", back);
		if (last)
			free(last);
		free(back);
		i++;
	}
}

void	print_export1(t_cmd *cmd, int *fdpipe, int *i, int j)
{
	int			pid;
	extern char	**environ;

	i[1] = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		close_pipe(NULL, cmd, fdpipe);
		ft_print_export(i[0], j);
		exit(0);
	}
	wait_process(NULL, cmd, fdpipe, environ);
	wait(NULL);
	dup2(i[1], STDOUT_FILENO);
}
