# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 16:02:00 by y klaurier        #+#    #+#              #
#    Updated: 2022/11/08 21:58:32 by anrechai         ###   ########.fr        #
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
				lexer2.c\
				parser.c \
				parser_pipe.c\
				parser_in.c\
				parser_out.c\
				parser_norme.c\
				parser_k.c \
				utils_minishell.c\
				utils_minishell2.c\
				redirection.c\
				parser_limiter.c \
				organizer.c\
				organizer2.c\
				organizer3.c\
				exec.c\
				organizer_exec.c

OBJS		=	${SRCS:.c=.o}

NAME		=	minishell

# FLAG		=	-Wall -Wextra -Werror

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
