/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:34:37 by eda-mata          #+#    #+#             */
/*   Updated: 2024/12/02 08:58:41 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reprompt(int sig)
{
	char	**environ;
	int		fd;

	if (g_sinal == 0 || g_sinal == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		fd = open(".status", O_CREAT | O_RDWR, 777);
		if (fd >= 0)
			write(fd, "130", 3);
		if (g_sinal == 0)
			rl_redisplay();
	}
	else
	{
		g_sinal = -1;
		rl_on_new_line();
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
	return ;
}
