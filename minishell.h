/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:02:20 by eda-mata          #+#    #+#             */
/*   Updated: 2024/12/02 15:16:49 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

extern int	g_sinal;

typedef struct s_cmd
{
	char			*comand;
	char			**parm;
	struct s_cmd	*next;
	struct s_ft_dup	*ft_dup;
	int				status;
}t_cmd;
typedef struct s_ft_dup
{
	char			*str;
	struct s_ft_dup	*next;
}t_ft_dup;

void	reprompt(int sig);
char	**ft_split_expand(char *str, int status);
void	input_param(char *cmd, char **environ, t_ft_dup **ft_dup_rai);
int		countmatriz(char **params);
int		echo(char **str);
int		intern(t_cmd *cmd, char **environ, int *fdpipe);

void	liberar(t_cmd *cmd);
void	free_matriz(char **str);
void	wait_process(int *in_fd, t_cmd *cmd, int *fdpipe, char **environ);
void	the_status(char *status);
void	close_pipe(int *in_fd, t_cmd *cmd, int *fdpipe);
void	redimensionar(t_cmd *cmd, char **environ, int *in_fd);
char	**ft_split_sep(char *str, char c);
char	*find_comand(char **path, char *comand);
int		execute(char *dir, char **arg, char **environ);
char	*ft_join_not_space(char *str, char *c);
void	ft_unset(char **param, t_cmd *cmd);
int		print_export(char **environ, char **param, t_cmd *cmd);
int		print_env(char **environ, char **param);
int		cd(char **str, t_cmd *cmd, char **environ);
int		verify_pipe(char **params);
char	*afterequal(char *str);
char	*backequal(char *str);
int		make_redi(char **arg);
char	**arguments(char **arg, int *var);
void	print_status(t_cmd *cmd);
int		ft_isdigit(char *c);
int		verify_limit(char str);
void	inputlimites(char **res, int *k, char *str, int *j);
void	ft_creat_file(char **arg);
void	remove_caracter(char **str, char caracter);
int		verify_var(char *str);
int		find_var(char *var, char **envirom);
void	ft_red_hedoc(t_cmd *cmd, int status);
int		ft_exit(char **number, t_cmd *cmd);
char	*getvar(char *str, int *i);
int		fechamento(char *str, char c, int i);
int		sep(char *str, char c);
void	input_status(int status, char **res, int *i, int *j);
char	*ft_remove_char15(char *delimiter);
int		ft_verify_next_red(t_cmd *cmd);
int		liberar_dup(void);
//splites  version

//environment_checker
void	add_var(char **argv, t_cmd *cmd);
int		expand(char **res, char *str, int k, int j);
int		atualiazar_enverement(char **environ, char *str, char *var);
//void atualiazar_enverement(char **environ, const char *var, const char *name);

// pack
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strlen(char *str);
char	*ft_strcpy(char *str1, char *str2);
int		verify_char(char *str, int i, char limite);
void	ft_swap_pwd2(void);
void	ft_load_dup(t_cmd *cmd, t_ft_dup **ft_dup_raiz);
int		ft_start(char **str);
void	ft_swap_pwd(void);
//sep
void	sep3(char *str, int *count, int *i, char *v);
void	sep4(char *str, int *count, int *i, char *v);
void	sep5(char *str, int *count, int *i, char *v);
void	sep6(char *str, int *count, int *i, char *v);
void	sep7(char *str, int *count, int *i, char *v);

int		tratar_aspas(char *str, int *i, char *asp);

void	print_export1(t_cmd *cmd, int *fdpipe, int *i, int j);
//pipline
int		pular_espacos(char *str, int *i);
int		tratar_pipe_condicional(char *str, int *i, int *count);
int		tratar_caractere_c(char *str, int *i, char c, int *count);
int		comands_externs1(t_cmd *cmd, int **fdpipe, pid_t pid, sig_t	si);
int		limite_red_space(char *str, int i, char a);
int		limite_red(char *str, int i);
//minipack
int		ft_strcmp2(char *str1, char c);
char	**ft_strdup2(char **str);
int		ft_strlen2(char *str);
void	ft_red_hedoc(t_cmd *cmd, int status);
void	aux_redirection(t_cmd *cmd, int *i, int status);
int		ft_write_input(t_cmd *cmd, int *i);
void	ft_write_temp(t_cmd *cmd, int *i, int status);
void	aux_unset(char **environ, char **param, int count, int nparam);
void	aux_add_var(char **argv, char *enverement[], int *i, t_cmd *cmd);
char	**ft_write_split_sep(char *str, char c, int *i);
void	ft_write_res2(char **res, int *i, char *str, int *k);
void	ft_write_res(char *str, int *i, char **res, int *k);
int		mini_split_expand(char **sp, int *i, char *str, int *j);
int		mini_split(char **sp, int *i, char *str, int j);
int		intern(t_cmd *cmd, char **environ, int *in_fd);
char	*ft_get_path(t_cmd *cmd);
int		comands_extern(t_cmd *cmd, char **environ, int *in_fd, char *bin);
void	execute_extern(t_cmd *cmd, char **environ, int *in_fd, char *bin);
int		comands_interns(t_cmd *cmd, char **environ, int *status, int *fdpipe);
char	*ft_expand_riredoc(char *str, int status);
void	handle_heredoc(char *delimiter, int status);
int		ft_expandvar_2(char *str, char *res, int j);
void	ft_sigquit(int sign);
void	ft_exit_130(int sign);
char	*get_next_line(int fd);
void	ft_new_dup(t_cmd *cmd, char *str);
void	ft_trunc_dup(t_ft_dup	*novo, t_ft_dup *last, char *str);
void	main_aux(char *cmd, char **environ, t_ft_dup **ft_dup_raiz);
int		space_aux(char *str);
int		ft_verify_comand(char *str);
int		ft_check_comand(char *str);
void	ft_close_asp(char *str, int *i, char c);
int		verify_bin(char *str);
#endif
