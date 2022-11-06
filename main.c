/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/06 22:46:15 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*input;
	t_utils	*utils;
	t_exec	*exec;
	int		i;

	exec = malloc(sizeof(t_exec));
	utils = malloc(sizeof(t_utils));
	utils->home_str = NULL;
	env = ft_init_fill_env(envp);
	lex = malloc(sizeof(t_lex));
	input = NULL;
	while (1)
	{
		input = readline(">");
		add_history(input);
		ft_lexer(input, lex);
		if (ft_parser_k(lex, env) == 0) // $ + quotes
		{
			ft_organizer(&lex); //virer espace et quotes
			if (ft_parser(lex) == 0)
			{                //parser redirection et pipe
				ft_print_lex_k(lex);
				ft_heredoc(lex, env);
				ft_redirection(lex); // MODIFIER POUR OUVRIR LES FICHIER AVEC A NOUVELLE LISTE CHAINEE EXEC
				ft_organizer_exec(lex, exec, env);
			}
		}
		printf("afficher les tab 2 d\n");
		// ft_print_2_d_tab_test(exec->path);
		printf("\n\ntab commande = \n");
		ft_print_2_d_tab_test(exec->cmd);
		printf("\n\n tab file = \n");
		// printf("tab[0] = %s\n", exec->file);
		ft_print_2_d_tab_test(exec->file);

		// // ft_all_builtin(lex, env, utils);
		// 	// { //parser redirection et pipe
		// 		// ft_heredoc(lex, env);
		// 		// ft_redirection(lex);
		// 			// MODIFIER POUR OUVRIR LES FICHIER AVEC A NOUVELLE LISTE CHAINEE EXEC
		// 		ft_print_lex_k(lex);
		// 		// ft_organizer_exec(lex, exec, env);
			// }
		// }
		// i = 0;
		// REDIRECTION HERE DOC ET OPEN
		// FT ORGANIZER2 VIRER ESPACE + VIRER LES PIPE && NEW LIST POUR EXECVE
		// EXECVE
		// SIGNAUX
		// RETOUR ERREUR VARIABLE GLOBALE
		// (void)exec;
		free(input);
		// free(history);
		// ft_free(lex, env, utils);
		// return (0);
	}
	(void)i;
	(void)exec;
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

int	ft_heredoc(t_lex *lex, t_env *env)
{
	t_lex	*tmp;
	int		fd;
	char	*limiter;
	char	*input;
	char	*file;

	file = ".HEREDOC";
	tmp = lex;
	fd = 0;
	while (tmp->token != TOK_TOTO && tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->token == TOK_TOTO)
	{
		if (lex->next != NULL)
			tmp = tmp->next;
		if (tmp->next == NULL)
		{
			limiter = NULL;
			input = NULL;
		}
		else
		{
			limiter = tmp->next->str;
			input = limiter + 1;
		}
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0744);
		while (1)
		{
			input = readline(" >>");
			if (ft_strlen(input) == 0 && limiter != NULL)
				ft_organizer_heredoc(input, fd);
			else if (ft_strlen(input) != 0 && limiter == NULL)
				ft_organizer_heredoc(input, fd);
			else if (ft_strlen(input) == 0 && limiter == NULL)
				break ;
			else if (ft_compare(input, limiter) != SUCCESS)
				ft_organizer_heredoc(input, fd);
			else
				break ;
		}
	}
	else
	{
		return (1);
	}
	(void)env;
	return (0);
}
