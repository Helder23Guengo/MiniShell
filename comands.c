/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:15:15 by hguengo           #+#    #+#             */
/*   Updated: 2024/12/02 13:41:44 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	aux_comands_interns(t_cmd *cmd, char **environ, char **argv, int *status)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd->comand, "exit") == 0)
		ft_exit(argv, cmd);
	else if (ft_strcmp(cmd->comand, "cd") == 0)
		i = cd(argv, cmd, environ);
	else if (ft_strcmp(cmd->comand, "unset") == 0)
		ft_unset(argv, cmd);
	else if (ft_strcmp(cmd->comand, "export") == 0)
		i = print_export(environ, argv, cmd);
	else
	{
		(*status) = 0;
		return (1);
	}
	(*status) += i;
	return (0);
}

void	comand_interns1(t_cmd *cmd, int *status, char **argv, int *i)
{
	int				pid;
	int				dfd;
	extern char		**environ;

	dfd = dup(1);
	argv = arguments(cmd->parm, i);
	pid = fork();
	if (pid == 0)
	{
		if (ft_strcmp2(cmd->comand, '<') == 0
			|| ft_strcmp2(cmd->comand, '>') == 0
			|| ft_strcmp(cmd->comand, "exit") == 0
			|| ft_strcmp(cmd->comand, "cd") == 0
			|| ft_strcmp(cmd->comand, "unset") == 0
			|| ft_strcmp(cmd->comand, "export") == 0)
			ft_red_hedoc(cmd, (*status));
		exit(0);
	}
	else
	{
		wait(NULL);
		(*i) = aux_comands_interns(cmd, environ, argv, status);
		free_matriz(argv);
		dup2(dfd, 1);
	}
}

int	comands_interns(t_cmd *cmd, char **environ, int *status, int *in_fd)
{
	int		i;
	char	**argv;
	int		dfd;

	if (((ft_strcmp(cmd->comand, "<<") == 0
				|| ft_strcmp(cmd->comand, ">>") == 0)
			|| ((ft_strcmp(cmd->comand, "<") == 0
					|| ft_strcmp(cmd->comand, ">") == 0)))
		&& cmd->parm[1] && cmd->parm[2])
	{
		redimensionar(cmd, environ, in_fd);
		return (0);
	}
	comand_interns1(cmd, status, argv, &i);
	return (i);
}
int	verify_bin(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '/' || str[i] == '.')
	{
		if (access(str, X_OK)==-1)
			return (-1);
	}
	return (0);
}
void	execute_extern(t_cmd *cmd, char **environ, int *in_fd, char *bin)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	if (ft_strcmp(cmd->comand, "echo") == 0)
		echo(cmd->parm);
	else if (ft_strcmp(cmd->comand, "env") == 0)
		print_env(environ, cmd->parm);
	else if (ft_strcmp(cmd->comand, "pwd") == 0)
	{
		printf("%s\n", pwd);
		exit(0);
	}
	else if (bin != NULL && verify_bin(cmd->comand)==0)
		execute(bin, cmd->parm, environ);
	else if (access(cmd->comand, X_OK) == 0)
		execute(cmd->comand, cmd->parm, environ);
	else
		the_status(cmd->comand);
}

int	comands_extern(t_cmd *cmd, char **environ, int *in_fd, char *bin)
{
	int		fdpipe[2];
	int		*pipeline[2];
	pid_t	pid;
	sig_t	si;
	int		status;

	if (cmd->next)
		pipe(fdpipe);
	si = signal(SIGQUIT, ft_sigquit);
	pipeline[0] = fdpipe;
	pipeline[1] = in_fd;
	pid = fork();
	if (pid == 0)
	{
		close_pipe(in_fd, cmd, fdpipe);
		execute_extern(cmd, environ, in_fd, bin);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else
		status = comands_externs1(cmd, pipeline, pid, si);
	return (status);
}
