/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:11 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/29 13:21:40 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit1(void)
{
	printf("exit\n");
	exit(0);
}

void	ft_exit2(char **number)
{
	printf("exit\n");
	exit(ft_atoi(number[1]));
}

int	ft_exit(char **number, t_cmd *cmd)
{
	extern char	**environ;

	make_redi(cmd->parm);
	if (cmd->next)
		intern(cmd->next, environ, NULL);
	else if (g_sinal != 0)
		return (0);
	else if (countmatriz(number) >= 2 && ft_isdigit(number[1]) == 1)
	{
		printf("exit\nnumeric argument required\n");
		exit(2);
	}
	else if (countmatriz(number) == 1)
		ft_exit1();
	else if (countmatriz(number) > 2)
	{
		printf("exit: too many arguments\n");
		return (130);
	}
	else if (countmatriz(number) == 2)
		ft_exit2(number);
	return (0);
}

size_t	ft_strlen4(const char *str)
{
	size_t	contar;

	contar = 0;
	while (str[contar] != '\0')
		contar++;
	return (contar);
}
