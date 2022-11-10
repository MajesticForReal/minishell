/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 22:16:51 by anrechai         ###   ########.fr       */
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
	char	*input;
	t_utils	*utils;
	t_exec	*exec;

	lex = NULL;
	utils = NULL;
	exec = NULL;
	input = NULL;
	while (1)
	{
		input = readline(">");
		env = ft_init_fill_env(envp);
		if (ft_init(&lex, &utils, &exec) == -1)
			return (-1);
		add_history(input);
		ft_lexer(input, lex);
		if (ft_parser_k(lex, env) == 0)
		{
			ft_organizer(&lex);
			if (ft_parser(lex) == 0)
			{
				ft_organizer_exec(lex, exec, env);
				ft_exec(exec, env, utils, lex);
			}
		}
		ft_free(lex, env, utils, exec);
		free(input);
	}
	(void)argc;
	(void)argv;
	(void)exec;
	(void)lex;
	(void)input;
	(void)env;
}