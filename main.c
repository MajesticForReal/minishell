/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/02 17:08:59 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_lex *lex, t_env *env, t_utils *utils)
{
	t_lex *tmp;
	t_env *tmp2;
	
	while (lex != NULL && lex->next != NULL)
	{
		tmp = lex;
		if (lex->next != NULL)
			lex = lex->next;
		free(tmp->str);
		free(tmp);
	}
	free(lex->str);
	free(lex);
	while (env != NULL && env->next != NULL)
	{
		tmp2 = env;
		if (env->next != NULL)
		env = env->next;
		free(tmp2->str);
		free(tmp2);
	}
	free(env->str);
	free(env);
	if (utils->home_str != NULL)
		free(utils->home_str);
	free(utils);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_lex	*lex;
	t_env	*env;
	char	*input;
	t_utils *utils;
	// char	*history;


	utils = malloc(sizeof(t_utils));
	utils->home_str = NULL;
	env = ft_init_fill_env(envp);
	lex = malloc(sizeof(t_lex));
	input = NULL;
	// history = NULL;
	while (1)
	{
		// input = argv[1];
		input = readline(">");
		add_history(input);
		ft_lexer(input, lex);
		if (ft_parser_k(lex, env) == 0) // $ + quotes
		{
			ft_organizer(&lex);        //virer espace et quotes
			ft_parser(lex);                //parser redirection et pipe
			ft_all_builtin(lex, env, utils);
		}
		// ft_print_lex_k(lex);
		// ft_print_list(lex);
		// REDIRECTION HERE DOC ET OPEN
		// FT ORGANIZER2 VIRER LES PIPE && NEW LIST POUR EXECVE
		// EXECVE
		free(input);
		// free(history);
		// ft_free(lex, env, utils);
		// return (0);
	}
	(void)env;
	(void)input;
	(void)argc;
	(void)argv;
}

void	ft_all_builtin(t_lex *lex, t_env *env, t_utils *utils)
{
	if (lex->str != NULL)
	{
		if (ft_compare(lex->str, "pwd") == SUCCESS)
			ft_builtin_pwd(1);
		else if (ft_compare(lex->str, "cd") == SUCCESS)
			ft_builtin_cd_all(lex, env, utils);
		else if (ft_compare(lex->str, "echo") == SUCCESS)
			ft_builtin_echo_all(lex->next, env);
		else if (ft_compare(lex->str, "env") == SUCCESS)
			ft_print_list_env(env);
		else if (ft_compare(lex->str, "unset") == SUCCESS)
			ft_unset_var(lex, env);
		else if (ft_compare(lex->str, "export") == SUCCESS)
			ft_export_var(lex, env);
	}
}