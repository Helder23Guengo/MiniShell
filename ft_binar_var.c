/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binar_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eda-mata <eda-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:42:23 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/23 00:52:53 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_insert_param(char **argv, char **arg, int *i)
{
	while (arg[i[0]] && !((ft_strcmp2(arg[i[0]], '>') == 0)
			|| (ft_strcmp2(arg[i[0]], '<') == 0)))
	{
		argv[i[1]] = ft_strdup(arg[i[0]]);
		++i[0];
		++i[1];
	}
	if (arg[i[0]] && (((ft_strcmp(arg[i[0]], ">>") == 0 && arg[i[0] + 1])
				|| (ft_strcmp(arg[i[0]], ">") == 0 && arg[i[0] + 1]))
			|| ((ft_strcmp(arg[i[0]], "<<") == 0 && arg[i[0] + 1])
				|| (ft_strcmp(arg[i[0]], "<") == 0 && arg[i[0] + 1]))))
		i[0] += 2;
	else if (arg[i[0]])
		i[0]++;
}

char	**arguments(char **arg, int *var)
{
	char	**argv;
	int		i[2];

	argv = malloc((countmatriz(arg) + 1) * sizeof(char *));
	i[0] = 0;
	i[1] = 0;
	while (arg[i[0]])
		ft_insert_param(argv, arg, i);
	argv[i[1]] = NULL;
	*var = i[0];
	return (argv);
}

int	execute(char *dir, char **arg, char **environ)
{
	int		i;
	int		status;
	char	**argv;

	argv = arguments(arg, &i);
	i = make_redi(arg);
	i = 0;
	remove_caracter(argv, 15);
	if (i == 0)
		exit(execve(dir, argv, environ));
}
