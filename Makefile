# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 16:02:00 by y klaurier        #+#    #+#              #
#    Updated: 2022/11/15 21:34:49 by anrechai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		=	main.c \
				heredoc_no_cmd.c \
				builtin_cd.c \
				builtin_cd2.c \
				builtin_echo.c \
				builtin_echo_2.c \
				builtin_env.c \
				builtin_env2.c \
				builtin_export.c \
				builtin_export_2.c \
				builtin_export_3.c \
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
				utils_minishell3.c\
				utils_minishell4.c\
				parser_limiter.c \
				is_not_valid_n.c\
				organizer.c\
				organizer2.c\
				organizer3.c\
				open.c\
				exec.c\
				exec2.c\
				exec_no_pipe.c\
				exec_no_pipe_2.c\
				exec_w_pipe.c\
				exec_w_pipe2.c\
				heredoc_doll.c\
				heredoc.c\
				var_doll.c \
				doll_special_char.c \
				doll_with_num.c \
				dollar.c \
				dollar_2.c \
				fill_tab_file.c \
				fill_tab_cmd.c \
				signal.c \
				itoa.c \
				doll_exit.c\
				ft_free.c\
				supp_list.c\
				ft_init.c\
				organizer_exec.c

OBJS		=	${SRCS:.c=.o}

NAME		=	minishell

FLAG		=	-Wall -Wextra -Werror

HEADER		=	minishell.h

.c.o:
			cc ${FLAG} -c $< -o $@ -I./


$(NAME):	$(OBJS)
			cc $(FLAGS) $(OBJS) -lreadline -o $(NAME) 

all:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		fclean clean re all bonus
