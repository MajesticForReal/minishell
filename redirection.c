/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:44:55 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/28 16:57:30 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_lex *lex)
{
	while(lex->next != NULL)
	{
		if(lex->token == TOK_IN && lex->next->token == TOK_WORD)
			 open(lex->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		lex = lex->next;
	}
}
