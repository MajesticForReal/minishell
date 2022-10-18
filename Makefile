# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 16:02:00 by y klaurier        #+#    #+#              #
#    Updated: 2022/10/18 16:19:30 by anrechai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		=	main.c \
				split.c \
				utils_exec.c \
				main_exec.c \
				exeptional_case_pipex.c \
				exec_cmd_fork.c \
				utils_minishell.c \
				free_pipex.c \
				get_path_and_cmd_pipex.c \
				builtin.c\
				lexer.c


OBJS		=	${SRCS:.c=.o}

NAME		=	minishell

FLAG		=	-Wall -Wextra -Werror

HEADER		=	minishell.h

.c.o:
			gcc ${FLAG} -c $< -o $@ -I./


$(NAME):	$(OBJS)
			gcc $(FLAGS) $(OBJS) -lreadline -o $(NAME) 

all:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		fclean clean re all bonus