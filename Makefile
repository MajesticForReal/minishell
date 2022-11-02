# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 16:02:00 by y klaurier        #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/11/02 17:14:01 by klaurier         ###   ########.fr        #
=======
#    Updated: 2022/11/02 19:34:37 by anrechai         ###   ########.fr        #
>>>>>>> 77781b2fc7a6252d0628862589334f7e87870e19
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
<<<<<<< HEAD
				redirection.c\
				parser_limiter.c \
				organizer.c
=======
				organizer.c\
>>>>>>> 77781b2fc7a6252d0628862589334f7e87870e19

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
