# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    xxCreated: 2022/06/27 16:02:59 by klaurier          #+#    #+#            #
#    Updated: 2022/06/28 14:05:41 by klaurier         ###   ########.fr        #
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
				builtin.c


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
