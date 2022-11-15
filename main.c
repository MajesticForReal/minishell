/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 17:58:16 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	t_exec	*tmp2;

	ft_close_files(utils->infile, utils->outfile);
	ft_free_lex(lex);
	while (exec != NULL)
	{
		ft_free_exec(exec);
		if (exec->next != NULL)
		{
			tmp2 = exec;
			exec = exec->next;
			free(tmp2);
		}
		else
		{
			free(exec);
			break ;
		}
	}
	ft_free_env(env);
	ft_free_export(utils);
	ft_free_utils(utils);
}

int	ft_start(t_lex *lex, t_utils *utils, t_exec *exec, char **envp)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("minishell > ");
		if (ft_input(input) == 0)
		{
			if (ft_init(&lex, &utils, envp) == 0)
				if (ft_init2(&lex, &utils, &exec) == -1)
					return (-1);
			add_history(input);
			ft_lexer(input, lex);
			if (ft_parser_k(lex, utils->env, utils) == SUCCESS)
			{
				ft_organizer(&lex);
				if (ft_parser(lex, utils) == 0)
					if (ft_organizer_exec(lex, exec, utils) == SUCCESS)
						ft_exec(exec, utils, lex);
			}
			ft_free(lex, utils->env, utils, exec);
			free(input);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lex	*lex;
	t_utils	*utils;
	t_exec	*exec;

	lex = NULL;
	utils = NULL;
	exec = NULL;
	signal(SIGINT, ft_detect_sig);
	signal(SIGQUIT, ft_detect_sig);
	if (argc == 1 && argv != NULL)
		ft_start(lex, utils, exec, envp);
	return (0);
}
