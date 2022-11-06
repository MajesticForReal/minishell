/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:31:10 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/06 22:07:42 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_quotes2(t_lex **lex, t_lex *lex_tmp)
{
	while ((*lex) != NULL && (*lex)->next != NULL)
	{
		if ((*lex)->next->token == TOK_DQ || (*lex)->next->token == TOK_SQ)
		{
			lex_tmp = (*lex)->next;
			(*lex)->next = (*lex)->next->next;
			free(lex_tmp->str);
			free(lex_tmp);
		}
		if ((*lex)->next != NULL && (*lex)->next->token != TOK_DQ
			&& (*lex)->next->token != TOK_SQ)
			(*lex) = (*lex)->next;
	}
	return ;
}

void	ft_clear_quotes(t_lex **lex)
{
	t_lex	*first;
	t_lex	*lex_tmp;
	t_lex	*new;

	while (((*lex)->token == TOK_DQ || (*lex)->token == TOK_SQ)
		&& (*lex)->next != NULL)
	{
		lex_tmp = (*lex);
		(*lex) = (*lex)->next;
		free(lex_tmp->str);
		free(lex_tmp);
	}
	first = (*lex);
	ft_clear_quotes2(lex, lex_tmp);
	if (((*lex)->token == TOK_DQ || (*lex)->token == TOK_SQ)
		&& (*lex)->next == NULL)
	{
		new = ft_initialize_struct();
		lex_tmp = (*lex);
		(*lex) = new;
		free(lex_tmp->str);
		free(lex_tmp);
	}
	else
		(*lex) = first;
}

void	ft_concat_clear(t_lex **lex)
{
	t_lex	*first;
	t_lex	*start;

	first = (*lex);
	start = (*lex);
	while ((*lex) != NULL && (*lex)->next != NULL)
	{
		if ((*lex) != NULL && (*lex)->next != NULL && (*lex)->token == TOK_WORD
			&& (*lex)->next->token == TOK_WORD)
		{
			ft_concat_clear2(lex, first);
			ft_concat_clear3(lex, first, start);
		}
		if ((*lex) != NULL && (*lex)->next != NULL)
		{
			(*lex) = (*lex)->next;
			if ((*lex)->token != TOK_WORD)
				start = (*lex);
		}
		else
			break ;
	}
	(*lex) = first;
}

void	ft_concat_clear2(t_lex **lex, t_lex *first)
{
	char	*newstr;
	t_lex	*lex_tmp;

	while ((*lex) != NULL && (*lex) == first && (*lex)->next != NULL
		&& (*lex)->next->token == TOK_WORD)
	{
		newstr = ft_concat2((*lex)->str, (*lex)->next->str);
		(*lex)->str = newstr;
		lex_tmp = (*lex)->next;
		if ((*lex)->next->next != NULL)
			(*lex)->next = (*lex)->next->next;
		else
			(*lex)->next = NULL;
		free(lex_tmp);
	}
}

void	ft_concat_clear3(t_lex **lex, t_lex *first, t_lex *start)
{
	t_lex	*lex_tmp;

	while ((*lex) != NULL && (*lex) != first && (*lex)->next != NULL
		&& (*lex)->next->token == TOK_WORD)
	{
		lex_tmp = ft_initialize_struct2((*lex)->str, (*lex)->next->str,
				(*lex)->next->next);
		start->next = lex_tmp;
		free((*lex)->next);
		free((*lex));
		(*lex) = lex_tmp;
	}
}
