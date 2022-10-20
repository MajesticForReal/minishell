/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:31:10 by anrechai          #+#    #+#             */
/*   Updated: 2022/10/20 18:29:52 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list(t_lex *lex)
{
	while (lex->next != NULL)
	{
		printf("%s\n", lex->str);
		lex = lex->next;
	}
	printf("%s\n", lex->str);
}

void	ft_organizer(t_lex *lex)
{
	ft_print_list(lex);
	while (lex != NULL)
	{
		if (lex->token == TOK_DQ || lex->token == TOK_SQ)
		{
			
		}
		lex = lex->next;
	}
}

// ft_del_struct(lex);