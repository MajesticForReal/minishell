/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 20:57:49 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exstat;

void	ft_free(t_lex *lex, t_env *env, t_utils *utils)
{
	t_lex	*tmp;
	t_env	*tmp2;

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
	// t_env	*export;
	char	*input;
	t_utils	*utils;
	t_exec	*exec;
	
	exec = malloc(sizeof(t_exec));
	utils = malloc(sizeof(t_utils));
	utils->home_str = NULL;
	env = ft_init_fill_env(envp);
	// export = ft_init_fill_env(envp);
	lex = malloc(sizeof(t_lex));
	
	// signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_detect_sig);
	signal(SIGQUIT, ft_detect_sig);
	
	while (1)
	{
	
		input = readline("minishell > ");
		if(!input)
		{
			ft_putstr_fd("exit", 2);
			ft_putstr_fd("\n", 2);
			g_exstat = 0;
			return(1) ;
		}
		add_history(input);
		ft_lexer(input, lex);
		if (ft_parser_k(lex, env) == 0) // $ + quotes
		{
			ft_organizer(&lex); //virer espace et quotes
			if (ft_parser(lex) == 0)
			{                //parser redirection et pipe
				ft_redirection(lex); // MODIFIER POUR OUVRIR LES FICHIER AVEC A NOUVELLE LISTE CHAINEE EXEC
				ft_organizer_exec(lex, exec, env);
			}
		}
		// ft_print_lex_k(lex);
		ft_all_builtin(lex, env, utils);
		// ft_print_3_exec(exec);
		// ft_print_lex_k(lex);
		free(input);
	}
	(void)argc;
	(void)argv;
	(void)exec;
	(void)lex;
	(void)input;
	(void)env;
}