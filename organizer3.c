/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:50:22 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/10 00:57:58 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_dq(t_lex **lex)
{
	(*lex) = (*lex)->next;
	while (lex != NULL && (*lex)->next != NULL && (*lex)->token != TOK_DQ)
	{
		if ((*lex)->token != TOK_DOLL)
			(*lex)->token = TOK_WORD;
		(*lex) = (*lex)->next;
	}
	if ((*lex)->next != NULL)
		(*lex) = (*lex)->next;
}

void	ft_check_sq(t_lex **lex)
{
	(*lex) = (*lex)->next;
	while (lex != NULL && (*lex)->next != NULL && (*lex)->token != TOK_SQ)
	{
		(*lex)->token = TOK_WORD;
		(*lex) = (*lex)->next;
	}
	if ((*lex)->next != NULL)
		(*lex) = (*lex)->next;
}

int	ft_check_quotes(t_lex *lex)
{
	t_lex	*first;

	first = lex;
	while (lex != NULL)
	{
		if (lex != NULL && lex->next != NULL && lex->token == TOK_DQ)
			ft_check_dq(&lex);
		else if (lex != NULL && lex->next != NULL && lex->token == TOK_SQ)
			ft_check_sq(&lex);
		else
			lex = lex->next;
	}
	lex = first;
	if (ft_check_quotes2(lex) == -1)
		return (-1);
	return (0);
}

int	ft_check_quotes2(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex != NULL)
	{
		if (lex->token == TOK_DQ || lex->token == TOK_SQ)
		{
			if (i == 0)
			{
				i = ft_quotes(lex);
				if (i != 1)
				{
					return (-1);
				}
			}
			else
				return (0);
		}
		lex = lex->next;
	}
	return (0);
}
