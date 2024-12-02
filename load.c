/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:33:22 by eda-mata          #+#    #+#             */
/*   Updated: 2024/12/02 11:29:16 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_trunc(t_cmd	*novo, t_cmd *last, char *comand, char **params)
{
	novo->comand = ft_strdup(comand);
	novo->parm = ft_strdup2(params);
	novo->ft_dup = NULL;
	novo->next = NULL;
	last->next = novo;
}

void	new_comand(t_cmd **cmd, char *comand, char **params)
{
	t_cmd	*aux;
	t_cmd	*novo;
	t_cmd	*last;

	aux = *cmd;
	novo = malloc(1 * sizeof(t_cmd));
	if (!novo)
		return ;
	if (aux == NULL)
	{
		novo->comand = ft_strdup(comand);
		novo->parm = ft_strdup2(params);
		novo->ft_dup = NULL;
		novo->next = NULL;
		(*cmd) = novo;
		return ;
	}
	while (aux)
	{
		last = aux;
		aux = aux->next;
	}
	ft_trunc(novo, last, comand, params);
	return ;
}

void	ft_input(t_cmd **cmd, char **params)
{
	int			i;
	int			j;
	int			argc;
	char		**arg;

	i = 0;
	while (params[i])
	{
		j = i;
		argc = 0;
		arg = malloc((countmatriz(params) + 1) * sizeof(char *));
		while (params[i] && ft_strcmp(params[i], "|") != 0)
		{
			arg[argc] = ft_strdup(params[i]);
			i++;
			argc++;
		}
		arg[argc] = NULL;
		new_comand(&*cmd, params[j], arg);
		free_matriz(arg);
		if (!params[i])
			break ;
		i++;
	}
}

int	ft_read_status(int status)
{
	int					fd;
	char				status_char[4];
	int					i;

	fd = open(".status", O_RDONLY);
	if (fd != -1)
	{
		i = read(fd, status_char, sizeof(status_char));
		status_char[i] = '\0';
		unlink(".status");
		return (ft_atoi(status_char));
	}
	return (status);
}

void	input_param(char *cmd, char **environ, t_ft_dup **ft_dup_raiz)
{
	static int			status;
	char				**params;
	t_cmd				*raiz;
	t_cmd				*aux;

	raiz = NULL;
	status = ft_read_status(status);
	params = ft_split_expand(cmd, status);
	if (!params[0] || verify_pipe(params) == -1)
	{
		free_matriz(params);
		return ;
	}
	ft_input(&raiz, params);
	aux = raiz;
	g_sinal = 0;
	status = intern(&*aux, environ, NULL);
	g_sinal = 0;
	ft_load_dup(raiz, &*ft_dup_raiz);
	free_matriz(params);
	liberar(raiz);
}
