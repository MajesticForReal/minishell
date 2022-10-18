/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:41 by anrechai          #+#    #+#             */
/*   Updated: 2022/10/18 16:24:04 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char const *argv[])
{

	char	*input = NULL;
	// t_lexer *lexer;

	// lexer = malloc(sizeof(t_lexer));
	// ecriture d'un prompt

	// lecture de STDIN en boucle grace a readline et while(1)

	// pour que ca marche pour un pc qui n'a pas la biblioteque de readline
	// entrer sudo apt-get install libreadline-dev dans le terminal
	while(1)
	{
		input = readline("$>");
		if(ft_compare(input, "exit") == SUCCESS)
			return (0);
		else if(ft_compare(input, "pwd") == SUCCESS)
			ft_builtin_pwd();
		// else if(ft_compare(input, "cd") == SUCCESS)
			// ft_buitin_cd(input))
		// ft_lexer(input, &lexer);
		ft_lexer(input);
		free(input);
	}
    
	(void)input;
	(void)argc;
    (void)argv;
}

