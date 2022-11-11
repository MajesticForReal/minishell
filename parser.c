/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:32:17 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/06 22:52:23 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(t_lex *lex)
{
	t_lex	*start;

	start = lex;
	while (lex != NULL)
	{
		if (lex->token == TOK_PIPE)
		{
			if (ft_pipe(lex, start) == -1)
				return (-1);
		}
		else if (lex->token == TOK_IN)
		{
			if (ft_in(&lex) == -1)
				return (-1);
		}
		else if (lex->token == TOK_OUT)
		{
			if (ft_out(&lex) == -1)
				return (-1);
		}
		lex = lex->next;
	}
	return (0);
}

void	ft_tok_fromfrom(t_lex **lex)
{
	t_lex	*first;

	first = (*lex);
	while ((*lex) != NULL)
	{
		if ((*lex)->str[0] == '>' && (*lex)->str[1] == '>'
			&& (*lex)->str[2] == '\0')
			(*lex)->token = TOK_FROMFROM;
		(*lex) = (*lex)->next;
	}
	(*lex) = first;
}

void	ft_tok_toto(t_lex **lex)
{
	t_lex	*first;

	first = (*lex);
	while ((*lex) != NULL)
	{
		if ((*lex)->str[0] == '<' && (*lex)->str[1] == '<'
			&& (*lex)->str[2] == '\0')
			(*lex)->token = TOK_TOTO;
		(*lex) = (*lex)->next;
	}
	(*lex) = first;
}

int	ft_out(t_lex **lex)
{
	t_lex	*first;

	first = (*lex);
	ft_tok_fromfrom(lex);
	while ((*lex) != NULL)
	{
		if (ft_out_if(lex) == -1)
		{
			(*lex) = first;
			return (-1);
		}
		(*lex) = (*lex)->next;
	}
	(*lex) = first;
	return (0);
}

int	ft_in(t_lex **lex)
{
	t_lex	*first;

	first = (*lex);
	ft_tok_toto(lex);
	while ((*lex) != NULL)
	{
		if (ft_in_if(lex) == -1)
		{
			(*lex) = first;
			return (-1);
		}
		(*lex) = (*lex)->next;
	}
	(*lex) = first;
	return (0);
}
