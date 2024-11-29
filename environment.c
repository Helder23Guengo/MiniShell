/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:54:00 by eda-mata          #+#    #+#             */
/*   Updated: 2024/11/28 15:51:23 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(char **environ, char **param)
{
	int		i;
	int		j;
	char	**argv;
	char	*var;

	i = 0;
	argv = arguments(param, &i);
	i = 0;
	j = make_redi(param);
	while (environ[i] && countmatriz(argv) == 1 && j == 0)
	{
		var = afterequal(environ[i]);
		if (var != NULL)
		{
			printf("%s\n", environ[i]);
			free(var);
		}
		i++;
	}
	exit(0);
}

int	redir(char **str, int i)
{
	if (((ft_strcmp(str[i - 1], ">>") == 0) || ft_strcmp(str[i - 1], ">") == 0)
		|| ((ft_strcmp(str[i - 1], "<<") == 0)
			|| ft_strcmp(str[i - 1], "<") == 0))
		i--;
	if (str[i] && (ft_strcmp(str[i], "<<") == 0 || ft_strcmp(str[i], "<") == 0))
		printf("entrada de dados\n");
	else if ((str[i] && !str[i + 1]) && (ft_strcmp(str[i], ">>") == 0
			|| ft_strcmp(str[i], ">") == 0))
	{
		printf("syntax error near unexpected token\n");
		return (1);
	}
}

int	atualiazar_enverement(char **environ, char *str, char *var)
{
	int		i;
	char	*str1;

	i = 0;
	str1 = afterequal(str);
	i = find_var(var, environ);
	if (str1 != NULL)
	{
		environ[i] = str;
	}
	while (environ[i])
		i++;
	environ[i] = NULL;
	free(str1);
	return (i);
}

int	print_export(char **environ, char **param, t_cmd *cmd)
{
	int		i[2];
	char	**argv;
	int		fdpipe[2];
	int		j;

	i[0] = 0;
	if (cmd->next)
		pipe(fdpipe);
	argv = arguments(param, &i[0]);
	j = make_redi(param);
	make_redi(cmd->parm);
	if (redir(param, i[0]) == 1)
		return (1);
	if (countmatriz(argv) == 1 && j == 0)
		print_export1(cmd, fdpipe, i, j);
	else if (countmatriz(argv) > 1 && j == 0)
	{
		if (cmd->next)
			intern(cmd->next, environ, NULL);
		else
			add_var(argv, cmd);
	}
	free_matriz(argv);
	return (0);
}

void	ft_unset(char **param, t_cmd *cmd)
{
	int			count;
	int			nparam;
	extern char	**environ;
	int			i;

	count = countmatriz(param);
	if (cmd->next)
		intern(cmd->next, environ, NULL);
	else if (g_sinal != 0)
		return ;
	else if (count == 1)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	else
	{
		nparam = 1;
		aux_unset(environ, param, count, nparam);
	}
}
