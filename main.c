/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 00:22:00 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_lex *lex, t_utils *utils, t_exec *exec)
{
	t_exec	*tmp2;

	ft_free_lex(lex);
	ft_close_files(utils->infile, utils->outfile);
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
}

void	ft_free_exit(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	t_exec	*tmp2;

	ft_free_lex(lex);
	ft_close_files(utils->infile, utils->outfile);
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

int	ft_start(t_lex *lex, t_utils *utils, t_exec *exec)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("minishell > ");
		if (ft_input(input, utils) == 0)
		{
			if (ft_init(&lex, &utils, &exec) == -1)
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
			ft_free(lex, utils, exec);
			free(input);
		}
	}
}

t_utils	*ft_init_utils(t_utils *utils)
{
	utils = malloc(sizeof(t_utils));
	if (!utils)
		return (NULL);
	utils->env = NULL;
	utils->export = NULL;
	utils->home_str = NULL;
	utils->ambigous = 0;
	utils->cmd_n_found = 0;
	utils->infile = -1;
	utils->outfile = -1;
	return (utils);
}

int	main(int argc, char **argv, char **envp)
{
	t_lex	*lex;
	t_utils	*utils;
	t_exec	*exec;

	lex = NULL;
	exec = NULL;
	utils = NULL;
	utils = ft_init_utils(utils);
	if (!utils)
		return (-1);
	if (envp[0] != NULL)
	{
		utils->env = ft_init_fill_env(envp);
		utils->export = ft_copy_env(utils->env);
	}
	g_exstat = 0;
	signal(SIGINT, ft_detect_sig_parent);
	signal(SIGQUIT, SIG_IGN);
	if (argc == 1 && argv != NULL)
		ft_start(lex, utils, exec);
	ft_free_env(utils->env);
	ft_free_export(utils);
	ft_free_utils(utils);
	return (0);
}
