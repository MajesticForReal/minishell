/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 00:35:57 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	t_lex	*tmp;
	t_exec	*tmp2;
	t_env	*tmp3;
	int		i;

	if (utils->infile != -1)
		close(utils->infile);
	if (utils->outfile != -1)
		close(utils->outfile);
	while (lex != NULL)
	{
		if (lex->str != NULL)
			free(lex->str);
		if (lex->next != NULL)
		{
			tmp = lex;
			lex = lex->next;
			free(tmp);
		}
		else
		{
			free(lex);
			break ;
		}
	}
	i = 0;
	while (exec != NULL)
	{
		if (exec->str_cmd != NULL)
			free(exec->str_cmd);
		if (exec->heredoc != NULL)
			free(exec->heredoc);
		if (exec->cmd)
			free(exec->cmd);
		if (exec->path)
		{
			while (exec->path[i])
			{
				free(exec->path[i]);
				i++;
			}
			free(exec->path);
		}
		if (exec->file)
			free(exec->file);
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
	while (env != NULL)
	{
		if (env->str != NULL)
			free(env->str);
		if (env->next != NULL)
		{
			tmp3 = env;
			env = env->next;
			free(tmp3);
		}
		else
		{
			free(env);
			break ;
		}
	}
	while (utils->export != NULL)
	{
		if (utils->export->str != NULL)
			free(utils->export->str);
		if (utils->export->next != NULL)
		{
			tmp3 = utils->export;
			utils->export = utils->export->next;
			free(tmp3);
		}
		else
		{
			free(utils->export);
			break ;
		}
	}
	if (utils != NULL)
	{
		if (utils->home_str != NULL)
			free(utils->home_str);
		free(utils);
	}
	return ;
}

int	ft_init(t_lex **lex, t_utils **utils, t_exec **exec)
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
	(*utils)->env = NULL;
	(*utils)->export = NULL;
	(*utils)->home_str = NULL;
	(*utils)->ambigous = 0;
	(*utils)->cmd_n_found = 0;
	(*utils)->infile = -1;
	(*utils)->outfile = -1;
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

int	main(int argc, char **argv, char **envp)
{
	t_lex *lex;
	char *input;
	t_utils *utils;
	t_exec *exec;

	lex = NULL;
	utils = NULL;
	exec = NULL;
	input = NULL;

	signal(SIGINT, ft_detect_sig);
	signal(SIGQUIT, ft_detect_sig);
	while (1)
	{
		input = readline("minishell > ");
		if (!input)
		{
			// ft_free(lex, env, utils, exec);
			ft_putstr_fd("exit", 2);
			ft_putstr_fd("\n", 2);
			g_exstat = 0;
			return (1);
		}
		if (ft_init(&lex, &utils, &exec) == -1)
			return (-1);
		utils->env = ft_init_fill_env(envp);
		utils->export = ft_copy_env(utils->env);
		add_history(input);
		ft_lexer(input, lex);
		if (ft_parser_k(lex, utils->env, utils) == SUCCESS)
		{
			ft_organizer(&lex);
			if (ft_parser(lex, utils) == 0)
			{
				if (ft_organizer_exec(lex, exec, utils) == SUCCESS)
					ft_exec(exec, utils, lex);
			}
		}
		ft_free(lex, utils->env, utils, exec);
		free(input);
	}
	(void)argc;
	(void)argv;
}