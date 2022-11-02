/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:44:55 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/01 14:19:05 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_lex *lex)
{
	while(lex->next != NULL)
	{
		if(lex->token == TOK_OUT && lex->str[0] == '>'
			&& lex->str[1] == '\0' && lex->next == NULL)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);;
		}
		else if(lex->token == TOK_OUT && lex->str[0] == '>'
			&& lex->str[1] == '>' && lex->next == NULL)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);;
		}
		else if(lex->token == TOK_OUT && lex->next->token == TOK_WORD
			&& lex->str[0] == '>' && lex->str[1] == '\0')
			{
				printf(">");
				open(lex->next->str, O_CREAT | O_RDWR | O_TRUNC, 0744);
			}
		else if(lex->token == TOK_FROMFROM && lex->str[0] == '>'
			&& lex->str[1] == '>' && lex->str[2] == '\0'
			&& lex->next->token == TOK_WORD)
			{
				printf(">>");
				open(lex->next->str, O_CREAT | O_RDWR | O_TRUNC, 0744);
			}
		lex = lex->next;
	}
}