/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/12 22:28:34 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	t_lex	*tmp;
	t_exec	*tmp2;
	t_env	*tmp3;
	int		i;

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
	if (utils != NULL)
	{
		if (utils->home_str != NULL)
			free(utils->home_str);
		free(utils);
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
	(*utils)->home_str = NULL;
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
	t_lex	*lex;
	t_env	*env;
	t_env	*export;
	char	*input;
	t_utils	*utils;
	t_exec	*exec;

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
		env = ft_init_fill_env(envp);
		export = ft_init_fill_env(envp);
		if (ft_init(&lex, &utils, &exec) == -1)
			return (-1);
		add_history(input);
		ft_lexer(input, lex);
		if (ft_parser_k(lex, env, utils) == SUCCESS)
		{
			ft_organizer(&lex);
			if (ft_parser(lex, utils) == 0)
			{
				if(ft_organizer_exec(lex, exec, env, utils) == SUCCESS)
					ft_exec(exec, env, utils, lex, export);
				else
					printf("FAIL\n");
			}
		}
		ft_free(lex, env, utils, exec);
		free(input);
	}
	(void)argc;
	(void)export;
	(void)argv;
}