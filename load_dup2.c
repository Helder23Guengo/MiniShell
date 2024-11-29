/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eda-mata <eda-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:40:11 by hguengo           #+#    #+#             */
/*   Updated: 2024/11/28 16:24:10 by eda-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_dup_load(t_ft_dup **ft_dup_raiz, char *str)
{
	int			i;
	t_ft_dup	*aux;
	t_ft_dup	*novo;
	t_ft_dup	*last;

	i = 0;
	aux = *ft_dup_raiz;
	novo = malloc(1 * sizeof(t_ft_dup));
	if (!novo)
		return ;
	if (aux == NULL)
	{
		novo->str = str;
		novo->next = NULL;
		*ft_dup_raiz = novo;
		return ;
	}
	while (aux)
	{
		last = aux;
		aux = aux->next;
	}
	ft_trunc_dup(novo, last, str);
}

void	ft_load_dup(t_cmd *cmd, t_ft_dup **ft_dup_raiz)
{
	t_cmd		*aux;
	t_ft_dup	*aux2;
	t_ft_dup	*aux3;
	t_ft_dup	*last;
	t_ft_dup	*novo;

	aux = cmd;
	aux3 = *ft_dup_raiz;
	while (aux)
	{
		if (aux->ft_dup)
		{
			aux2 = aux->ft_dup;
			while (aux2)
			{
				ft_new_dup_load(&*ft_dup_raiz, aux2->str);
				aux2 = aux2->next;
			}
		}
		aux = aux->next;
	}
}

void	ft_swap_pwd(void)
{
	extern char	**environ;
	static char	old_pwd2[2048];
	char		old_pwd[1024];
	int			i;
	int			j;

	i = 0;
	j = 0;
	getcwd(old_pwd, sizeof(old_pwd));
	ft_strcpy(old_pwd2, "OLDPWD=");
	while (old_pwd[j])
	{
		old_pwd2[i + 7] = old_pwd[j++];
		i++;
	}
	old_pwd2[i + 7] = '\0';
	atualiazar_enverement(environ, old_pwd2, "OLDPWD");
}

void	ft_swap_pwd2(void)
{
	extern char	**environ;
	static char	old_pwd2[2048];
	char		old_pwd[1024];
	int			i;
	int			j;

	i = 0;
	j = 0;
	getcwd(old_pwd, sizeof(old_pwd));
	ft_strcpy(old_pwd2, "PWD=");
	while (old_pwd[j])
	{
		old_pwd2[i + 4] = old_pwd[j];
		++j;
		i++;
	}
	old_pwd2[i + 4] = '\0';
	atualiazar_enverement(environ, old_pwd2, "PWD");
}

int	ft_start(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (!str[i])
		return (1);
	while (str[i])
	{
		j = 0;
		if (str[i][j] != '-')
			return (i);
		if (str[i][j] == '-' && !str[i][j + 1])
			return (i);
		j++;
		while (str[i][j])
		{
			if (str[i][j] && str[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
