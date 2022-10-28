/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/28 18:34:31 by anrechai         ###   ########.fr       */
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
		if (ft_parser_kevin(lex) == 0) // $ + quotes
			ft_organizer(&lex);        //virer espace et quotes
		ft_parser(lex);                //parser redirection et pipe
		ft_print_list(lex);
		// FT ORGANIZER2 VIRER LES PIPE
		ft_all_builtin(lex, env);
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