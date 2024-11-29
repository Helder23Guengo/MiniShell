# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 16:05:52 by hguengo           #+#    #+#              #
#    Updated: 2024/11/28 16:08:15 by hguengo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

FILE = comands.c sep.c pipeline.c suport_props.c load_dup2.c   pipeline_aux.c execute_bin.c free.c intern.c load.c signal.c utils.c main.c environment.c utils2.c heredoc.c commands_aux.c minipack.c package.c ft_version_split.c  ft_environment_checker.c ft_binar_var.c  utilitario.c aux_heredoc.c  ft_aux_environment.c ft_version_split2.c ft_intern.c utils3.c aux_heredoc2.c  maxpack.c ft_exit_program.c 

OBJS = comands.o sep.o pipeline.o suport_props.o load_dup2.o  pipeline_aux.o execute_bin.o free.o intern.o load.o signal.o utils.o main.o environment.o utils2.o heredoc.o commands_aux.o minipack.o package.o ft_version_split.o ft_environment_checker.o ft_binar_var.o utilitario.o aux_heredoc.o ft_aux_environment.o ft_version_split2.o ft_intern.o utils3.o aux_heredoc2.o maxpack.o ft_exit_program.o

REF = -lreadline


all: $(NAME)

$(NAME):
	$(CC) $(FILE) -c
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(REF)

clean: 
	$(RM) $(OBJS)

fclean:clean
	$(RM) $(NAME)

re: fclean all

rec: fclean all
	$(RM) $(OBJS)
