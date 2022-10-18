# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 16:41:52 by klaurier          #+#    #+#              #
#    Updated: 2022/10/18 16:46:18 by klaurier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS 		=	main.c \
				split.c \
				utils_minishell.c \
				builtin_pwd.c \
				builtin_cd.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_export.c \
				builtin_unset.c \
				init_env.c \
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
