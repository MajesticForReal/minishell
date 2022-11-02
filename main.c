/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/02 17:09:15 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char **envp)
{
	t_lex	*lex;
	t_env	*env;
	char	*input;

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
			ft_organizer(&lex);        //virer espace et quotes
		}
		ft_parser(lex);                //parser redirection et pipe
		ft_print_lex_k(lex);
		ft_heredoc(lex, env);
		ft_print_lex_k(lex);
		ft_redirection(lex);

		// REDIRECTION ET OPEN
		// FT ORGANIZER2 VIRER LES PIPE && NEW LIST POUR EXECVE
		ft_all_builtin(lex, env);
		// EXECVE
		free(input);
	}
	(void)env;
	(void)input;
	(void)argc;
	(void)argv;
}

void	ft_all_builtin(t_lex *lex, t_env *env)
{
	if (lex->str != NULL)
	{
		if (ft_compare(lex->str, "pwd") == SUCCESS)
			ft_builtin_pwd(1);
		else if (ft_compare(lex->str, "cd") == SUCCESS)
			ft_builtin_cd_all(lex, env);
		else if (ft_compare(lex->str, "echo") == SUCCESS)
			ft_builtin_echo_all(lex, env);
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
	
	int	fd;
	char *limiter;
	char *input;
	char *file;
	
	file = ".HEREDOC";
	tmp = lex;
	fd = 0;
	while(tmp->token != TOK_TOTO && tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if(tmp->token == TOK_TOTO)
	{
		if(lex->next != NULL)
			tmp = tmp->next;
		// limiter = ft_parser_limiter(tmp);
		limiter = tmp->str;
		printf("limiter = %s\n", limiter);
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0744);
		while(ft_compare(input, limiter) != SUCCESS)
		{
			input = readline(" >>");
			ft_organizer_heredoc(input, fd);
		}
	}
	else
		{
			
			return (1);
		}
	(void)env;
	return(0);
}

