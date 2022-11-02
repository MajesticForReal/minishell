# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 16:02:00 by y klaurier        #+#    #+#              #
#    Updated: 2022/11/02 14:49:43 by klaurier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS 		=	main.c \
				builtin_cd.c \
				builtin_echo.c \
				builtin_export.c \
				builtin_pwd.c \
				builtin_unset.c \
				init_env.c \
				split.c \
				lexer.c \
				parser_redir.c \
				parser_k.c \
				utils_minishell.c\
				redirection.c\
				parser_limiter.c \
				organizer.c

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
