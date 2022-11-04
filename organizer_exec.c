/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:51:31 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/03 18:15:23 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_organizer_exec(t_lex *lex, t_exec *exec)
{
	int	nb_pipe;
	t_lex *first;
	
	nb_pipe = 1;
	first = lex;
	while (lex != NULL)
	{
		if (lex->token == TOK_PIPE)
			nb_pipe++;
		lex = lex->next;
	}
	printf("NB PIPE = %d\n", nb_pipe);
	lex = first;
	while (lex != NULL)
	{
		if (lex->token == TOK_SPACE)
			lex = lex->next;
		else if (lex->token == TOK_WORD)
		{
			// CMD ET WORD APRES = DOC EXISTANT
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_OUT)
		{
			// IF WORD AVANT = CMD WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = DOC NO SUCH FILE OR DIRECTORY JUSAQUA LA FIN OU != TOK WORD
			// IF PAS DE WORD AVANT WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = CMD 
			// ON REMPLACE LE CONTENU DU DOC
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_IN)
		{
			// WORD APRES = DOC EXISTANT ET WORD APRES CA = CMD PUIS WORD = DOC EXISTANT JUSQUA != TOK WORD
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_FROMFROM)
		{
			// IF WORD AVANT = CMD WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = DOC NO SUCH FILE OR DIRECTORY JUSAQUA LA FIN OU != TOK WORD
			// IF PAS DE WORD AVANT WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = CMD 
			// ON AJOUTE AU DOC SANS EFFACER CE QUI EXISTE DEJA DEDANS
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_TOTO)
		{
			// HEREDOC DONC AVANCER APRES LE WORD LIMITER
		}
		else if (lex->token == TOK_PIPE)
		{
			// ON VA REMPLIR LA LISTE SUIVANTE
			// ET ON PASSE LE PIPE DONC lex = lex->next
			// exec = exec->next;
		}
	}
	(void)exec;
}