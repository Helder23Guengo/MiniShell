/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:07:57 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/23 02:29:33 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_char15(char *delimiter)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(delimiter) + 1) * sizeof(char));
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] != 15)
		{
			str[j] = delimiter[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	free(delimiter);
	return (str);
}

int	ft_expandvar_2(char *str, char *res, int j)
{
	int	i;

	i = 0;
	while (str[i])
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (j);
}

void	ft_write_temp(t_cmd *cmd, int *i, int status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		handle_heredoc(cmd->parm[*i + 1], status);
		exit(0);
	}
	else
		wait(NULL);
	if (g_sinal == -1)
		printf("\n");
}

void	redimensionar_aux(t_cmd *cmd, char **environ, int *in_fd, int i)
{
	if (cmd->parm[i] && (ft_strcmp2(cmd->parm[i], '>') == 1
			&& ft_strcmp2(cmd->parm[i], '<') == 1))
	{
		free(cmd->comand);
		cmd->comand = ft_strdup(cmd->parm[i]);
		intern(cmd, environ, in_fd);
	}
	else
	{
		remove_caracter(cmd->parm, 15);
		ft_creat_file(cmd->parm);
		return ;
	}
}

void	redimensionar(t_cmd *cmd, char **environ, int *in_fd)
{
	int	i;

	i = 0;
	while (cmd->parm[i] && (ft_strcmp2(cmd->parm[i], '>') == 0
			|| ft_strcmp2(cmd->parm[i], '<') == 0))
	{
		if (cmd->parm[i] && cmd->parm[i + 1])
			i += 2;
		else
		{
			printf("syntax error near unexpected token\n");
			return ;
		}
	}
	redimensionar_aux(cmd, environ, in_fd, i);
}
