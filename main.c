/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:57:56 by eda-mata          #+#    #+#             */
/*   Updated: 2024/11/29 13:27:32 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sinal;

char	*plus_leval(void)
{
	extern char	**environ;
	int			level;
	char		*new_level;
	char		*new_variavel;

	level = ft_atoi(getenv("SHLVL")) + 1;
	new_level = ft_itoa(level);
	new_variavel = ft_join_not_space("SHLVL=", new_level);
	atualiazar_enverement(environ, new_variavel, "SHLVL");
	free(new_level);
	return (new_variavel);
}

void	printf_dup(t_ft_dup *ft_dup)
{
	t_ft_dup	*aux;
	t_ft_dup	*last;

	aux = ft_dup;
	while (aux)
	{
		last = aux;
		free(aux->str);
		aux = aux->next;
		free(last);
	}
}

void	ft_close_asp(char *str, int *i, char c)
{
	(*i)++;
	while (str[(*i)] && str[(*i)] != c)
	{
		(*i)++;
	}
	(*i)++;
}

int	ft_verify_comand(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
		{
			ft_close_asp(str, &i, str[i]);
		}
		if (str[i] && (str[i] == '>' || str[i] == '<'))
		{
			c = str[i];
			while (str[i] && str[i] == c)
				i++;
			while (str[i] && str[i] == ' ' || str[i] == '	')
				i++;
			if (!str[i] || str[i] == '<' || str[i] == '>')
				return (-1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	main(void)
{
	char		*cmd;
	char		**params;
	extern char	**environ;
	char		*level;
	t_ft_dup	*ft_dup_raiz;

	level = plus_leval();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &reprompt);
	ft_dup_raiz = NULL;
	while (1)
	{
		cmd = readline("prompt% ");
		if (!cmd)
			break ;
		if (ft_verify_comand(cmd) == -1 || sep(cmd, ' ') == -1)
			printf("syntax error near unexpected token\n");
		else
		{
			if (cmd[0])
				input_param(cmd, environ, &ft_dup_raiz);
		}
		add_history(cmd);
		free(cmd);
	}
	printf_dup(ft_dup_raiz);
	printf("exit\n");
	free(level);
}
