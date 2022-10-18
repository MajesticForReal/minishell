/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/18 16:48:24 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char const *argv[], char **envp)
{

    char	*input = NULL;
	t_env	*env;
	t_var	*var;
	
	var =  malloc(sizeof(t_var));
	if (var == NULL)
		return (-1);
	env = ft_init_fill_env(envp);
	// ft_print_list_env(env);
	// t_lexer *lexer;

	// lexer = malloc(sizeof(t_lexer));
	// ecriture d'un prompt

	// lecture de STDIN en boucle grace a readline et while(1)

	// pour que ca marche pour un pc qui n'a pas la biblioteque de readline
	// entrer sudo apt-get install libreadline-dev dans le terminal
	while(1)
	{
		input = readline("$>");
		ft_lexer(input);
		add_history(input);
		if(ft_compare(input, "exit") == SUCCESS)
			return (0);
		else if(ft_compare(input, "pwd") == SUCCESS)
			ft_builtin_pwd(1);
		else if(ft_compare(input, "cd") == SUCCESS)
			ft_builtin_cd_only(input, env);
		else if(ft_compare(input, "cd dossier") == SUCCESS || ft_compare(input, "cd dossier/") == SUCCESS)
			ft_builtin_cd_dir(input);
		else if(ft_compare(input, "cd dossier_2") == SUCCESS || ft_compare(input, "cd dossier_2/") == SUCCESS)
			ft_builtin_cd_dir(input);
		else if(ft_compare(input, "cd ..") == SUCCESS)
			ft_builtin_cd_back(input);
		else if(ft_compare(input, "cd ~") == SUCCESS)
			ft_builtin_cd_only(input, env);
		else if(ft_compare(input, "cd ~/") == SUCCESS)
			ft_builtin_cd_only(input, env);
		else if(ft_compare(input, "cd /") == SUCCESS)
			ft_builtin_cd_rac(input);
		else if(ft_compare(input, "echo salut") == SUCCESS)
			ft_builtin_echo(input);
		else if(ft_compare(input, "echo -nnn -nann salut") == SUCCESS)
			ft_builtin_echo_option_2(input);
		else if(ft_compare(input, "echo") == SUCCESS)
			ft_builtin_echo_only(input);
		else if(ft_compare(input, "env") == SUCCESS)
			ft_print_list_env(env);
		else if(ft_compare(input, "export var=\"salut\"") == SUCCESS)
			ft_export_var(input, env);
		else if(ft_compare(input, "unset var=\"salut\"") == SUCCESS)
			ft_unset_var(input, env);
		else if(ft_compare(input, "unset TERM_PROGRAM_VERSION=1.72.0") == SUCCESS)
			ft_unset_var(input, env);
		// ft_lexer(input, &lexer);
		free(input);
	}
    
	(void)env;
	(void)input;
	(void)argc;
    (void)argv;
}

void	test_signal(int code)
{
	printf("salut");
	(void)code;
}
