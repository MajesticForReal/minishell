/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:41 by anrechai          #+#    #+#             */
/*   Updated: 2022/10/18 17:10:42 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char const *argv[])
{
	t_lex *lex;

	lex = malloc(sizeof(t_lex));
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
		ft_lexer(input, lex);
		free(input);
	}
    
	(void)input;
	(void)argc;
    (void)argv;
}

