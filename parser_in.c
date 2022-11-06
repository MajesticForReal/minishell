/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:53:28 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/06 20:25:57 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_22(t_lex **lex)
{
	if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& ft_strlen((*lex)->str) == 4)
	{
		ft_putstr_fd("syntax error near unexpected token `<'\n",
			2);
		return (-1);
	}
	else if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& ft_strlen((*lex)->str) == 5)
	{
		ft_putstr_fd("syntax error near unexpected token `<<'\n",
			2);
		return (-1);
	}
	else if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& ft_strlen((*lex)->str) > 5)
	{
		ft_putstr_fd("syntax error near unexpected token `<<<'\n",
			2);
		return (-1);
	}
	return (0);
}

int	ft_in_2(t_lex **lex)
{
	if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& (*lex)->next->next == NULL && ft_strlen((*lex)->str) < 4)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			2);
		return (-1);
	}
	else if (ft_in_22(lex) == -1)
		return (-1);
	return (0);
}

int	ft_in_elseif_2(t_lex **lex)
{
	if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& ((*lex)->next->next->token != TOK_WORD
			&& (*lex)->next->next->token != TOK_DQ
			&& (*lex)->next->next->token != TOK_SQ
			&& (*lex)->next->next->token != TOK_DOLL))
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd((*lex)->next->next->str[0], 2);
		ft_putchar_fd((*lex)->next->next->str[1], 2);
		ft_putstr_fd("'\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_in_elseif_3(t_lex **lex)
{
	if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& ((*lex)->next->token != TOK_WORD && (*lex)->next->token != TOK_DQ
			&& (*lex)->next->token != TOK_SQ && (*lex)->next->token != TOK_DOLL
			&& (*lex)->next->token != TOK_SPACE))
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd((*lex)->next->str[0], 2);
		ft_putchar_fd((*lex)->next->str[1], 2);
		ft_putstr_fd("'\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_in_if(t_lex **lex)
{
	if ((*lex)->next != NULL && ((*lex)->token == TOK_IN
			|| (*lex)->token == TOK_TOTO) && (*lex)->next->token == TOK_SPACE
		&& ((*lex)->next->next == NULL
			|| (*lex)->next->next->token != TOK_WORD))
	{
		if ((*lex)->str != NULL && ((*lex)->token == TOK_IN
				|| (*lex)->token == TOK_TOTO))
		{
			if (ft_in_2(lex) == -1)
				return (-1);
			else if (ft_in_elseif_2(lex) == -1)
				return (-1);
		}
	}
	else if ((*lex)->str != NULL && ((*lex)->token == TOK_IN
			|| (*lex)->token == TOK_TOTO))
	{
		if (ft_in_3(lex) == -1)
			return (-1);
		else if (ft_in_elseif_3(lex) == -1)
			return (-1);
	}
	return (0);
}
