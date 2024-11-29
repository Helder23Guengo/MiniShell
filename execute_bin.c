/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:47:55 by eda-mata          #+#    #+#             */
/*   Updated: 2024/11/29 08:26:11 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_rediration(char **arg)
{
	int	last_redirect;
	int	i;

	i = 0;
	last_redirect = -1;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">>") == 0 || ft_strcmp(arg[i], ">") == 0)
			last_redirect = i;
		i++;
	}
	return (last_redirect);
}

void	ft_creat_file(char **arg)
{
	int	i;
	int	temp_fd;

	i = 0;
	while (arg[i])
	{
		if ((ft_strcmp(arg[i], ">>") == 0
				|| ft_strcmp(arg[i], ">") == 0) && arg[i + 1])
		{
			if (ft_strcmp(arg[i], ">>") == 0)
				temp_fd = open(arg[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				temp_fd = open(arg[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (temp_fd < 0)
			{
				perror("open");
				exit(0);
			}
			close(temp_fd);
			i++;
		}
		i++;
	}
}

int	verificar_redir(char **str)
{
	int		i;
	char	*ft_string;

	i = 0;
	while (str[i])
	{
		if ((ft_strcmp(str[i], ">>") == 0 || ft_strcmp(str[i], "<<") == 0)
			|| (ft_strcmp(str[i], ">") == 0 || ft_strcmp(str[i], "<") == 0))
		{
			if (ft_strcmp2(str[i + 1], '>') != 0
				&& ft_strcmp2(str[i + 1], '<') != 0)
				i += 2;
			else
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

void	aux_make_redi(char **arg, int last_redirect)
{
	int	fd;

	if (arg[last_redirect + 1])
	{
		if (ft_strcmp(arg[last_redirect], ">>") == 0)
			fd = open(arg[last_redirect + 1], O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else
			fd = open(arg[last_redirect + 1], O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
			exit(0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		printf("syntax error\n");
}

int	make_redi(char **arg)
{
	int	last_redirect;

	last_redirect = ft_last_rediration(arg);
	if (verificar_redir(arg) == -1)
	{
		printf("syntax error\n");
		return (1);
	}
	remove_caracter(arg, 15);
	ft_creat_file(arg);
	if (last_redirect != -1)
		aux_make_redi(arg, last_redirect);
	return (0);
}
