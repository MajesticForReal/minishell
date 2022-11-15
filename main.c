/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 16:53:21 by anrechai         ###   ########.fr       */
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

int	ft_init_utils(t_utils **utils, char **envp, t_lex **lex)
{
	(*utils) = malloc(sizeof(t_utils));
	if (!utils)
	{
		free((*lex));
		return (-1);
	}
	(*utils)->env = NULL;
	(*utils)->export = NULL;
	(*utils)->home_str = NULL;
	(*utils)->ambigous = 0;
	(*utils)->cmd_n_found = 0;
	(*utils)->infile = -1;
	(*utils)->outfile = -1;
	(*utils)->env = ft_init_fill_env(envp);
	(*utils)->export = ft_copy_env((*utils)->env);
	return (0);
}

int	ft_init_exec(t_exec **exec, t_utils **utils, t_lex **lex)
{
	(*exec) = malloc(sizeof(t_exec));
	if (!(*exec))
	{
		free((*utils));
		free((*lex));
		return (-1);
	}
	(*exec)->str_cmd = NULL;
	(*exec)->heredoc = NULL;
	(*exec)->next = NULL;
	(*exec)->cmd = NULL;
	(*exec)->path = NULL;
	(*exec)->file = NULL;
	return (0);
}

int	ft_init(t_lex **lex, t_utils **utils, t_exec **exec, char **envp)
{
	(*lex) = malloc(sizeof(t_lex));
	if (!(*lex))
		return (-1);
	(*lex)->str = NULL;
	(*lex)->next = NULL;
	(*utils) = malloc(sizeof(t_utils));
	if (!utils)
	{
		free((*lex));
		return (-1);
	}
	// lex = malloc(sizeof(t_lex));
	// if (!lex)
	// 	return (-1);
	// lex->str = NULL;
	// lex->next = NULL;
	// utils = malloc(sizeof(t_utils));
	// if (!utils)
	// {
	// 	free(lex);
	// 	return (-1);
	// }
	// if (ft_init_utils(&utils, envp, &lex) != 0)
	// 	return (-1);
	(*utils)->env = NULL;
	(*utils)->export = NULL;
	(*utils)->home_str = NULL;
	(*utils)->ambigous = 0;
	(*utils)->cmd_n_found = 0;
	(*utils)->infile = -1;
	(*utils)->outfile = -1;
	(*utils)->env = ft_init_fill_env(envp);
	(*utils)->export = ft_copy_env((*utils)->env);
	// if (ft_init_exec(&lex, &utils, &exec) != 0)
	// 	return (-1);
	(*exec) = malloc(sizeof(t_exec));
	if (!(*exec))
	{
		free((*utils));
		free((*lex));
		return (-1);
	}
	(*exec)->str_cmd = NULL;
	(*exec)->heredoc = NULL;
	(*exec)->next = NULL;
	(*exec)->cmd = NULL;
	(*exec)->path = NULL;
	(*exec)->file = NULL;
	return (0);
}

void	ft_exit(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	ft_free(lex, env, utils, exec);
	exit(EXIT_SUCCESS);
}

int	ft_input(char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd("\n", 2);
		g_exstat = 0;
		exit(EXIT_SUCCESS);
	}
	if (input[0] == '.' && input[1] == '\0')
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		return (-1);
	}
	if (input[0] == '.' && input[1] == '.' && input[2] == '\0')
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		return (-1);
	}
	if (input[0] == '.' && input[1] == ' ' && input[2] == '.')
	{
		ft_putstr_fd("minishell: .: .: is a directory\n", 2);
		return (-1);
	}
	return (0);
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
			if (ft_init(&lex, &utils, &exec, envp) == -1)
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
	t_lex *lex;
	t_utils *utils;
	t_exec *exec;

	lex = NULL;
	utils = NULL;
	exec = NULL;
	signal(SIGINT, ft_detect_sig);
	signal(SIGQUIT, ft_detect_sig);
	if (argc == 1 && argv != NULL)
		ft_start(lex, utils, exec, envp);
}