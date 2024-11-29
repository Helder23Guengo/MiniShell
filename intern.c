/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:46:00 by eda-mata          #+#    #+#             */
/*   Updated: 2024/11/28 15:47:16 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_arg(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (!str[i])
		return (1);
	if (str[i][j] != '-')
		return (0);
	j++;
	if (!str[i][j])
		return (0);
	while (str[i][j])
	{
		if (str[i][j] && str[i][j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	printecho(int verify, char **argv)
{
	int	i;

	i = ft_start(argv);
	if (countmatriz(argv) == 1)
	{
		printf("\n");
		return ;
	}
	if (!argv[i])
		return ;
	if (ft_strcmp(argv[i], "|") == 0)
		return ;
	while (((argv[i] != NULL) && ft_strcmp(argv[i], "|") < 0)
		&& (!(ft_strcmp(argv[i], ">>") == 0)
			&& !(ft_strcmp(argv[i], ">") == 0)))
	{
		argv[i] = ft_remove_char15(argv[i]);
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (verify == 0)
		printf("\n");
}

int	echo(char **str)
{
	int			verify;
	int			i;
	int			j;
	int			k;
	char		**argv;

	j = 1;
	k = 0;
	argv = arguments(str, &i);
	if (((ft_strcmp(str[i - 1], ">>") == 0) || ft_strcmp(str[i - 1], ">") == 0)
		|| ((ft_strcmp(str[i - 1], "<<") == 0)
			|| ft_strcmp(str[i - 1], "<") == 0))
		i--;
	if ((str[i] && !str[i + 1]) && (ft_strcmp(str[i], ">>") == 0
			|| ft_strcmp(str[i], ">") == 0))
	{
		printf("syntax error near unexpected token\n");
		exit(1);
	}
	verify = verify_arg(argv);
	j = make_redi(str);
	if (j == 0)
		printecho(verify, argv);
	free_matriz(argv);
	exit(0);
}

int	cd1(char **str, t_cmd *cmd, int i, char **environ)
{
	if (countmatriz(str) > 2)
	{
		printf("string not in pwd\n");
		return (1);
	}
	else if (cmd->next)
		intern(cmd->next, environ, NULL);
	else if ((ft_strcmp (str[i + 1], "..") == 0) && chdir("..") == 0)
	{
		ft_swap_pwd2();
		return (0);
	}
	else if (access(str[i + 1], F_OK | W_OK | X_OK) == 0)
	{
		if (chdir(str[i + 1]) == 0)
			ft_swap_pwd2();
		else
			return (2);
	}
	else
	{
		perror("no such file or directory");
		return (2);
	}
	return (0);
}

int	cd(char **str, t_cmd *cmd, char **environ)
{
	int	i;

	i = 0;
	make_redi(cmd->parm);
	ft_swap_pwd();
	if (countmatriz(str) == 1)
	{
		printf("syntax error near unexpected token\n");
		return (1);
	}
	return (cd1(str, cmd, i, environ));
	return (0);
}
