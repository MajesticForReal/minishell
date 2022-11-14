/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:02:05 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/15 00:30:21 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quotes(t_lex *lex)
{
	int	nb_dq;
	int	nb_sq;

	nb_dq = 0;
	nb_sq = 0;
	while (lex != NULL)
	{
		if (lex->token == TOK_DQ)
			nb_dq = nb_dq + ft_strlen(lex->str);
		else if (lex->token == TOK_SQ)
			nb_sq = nb_sq + ft_strlen(lex->str);
		lex = lex->next;
	}
	if (nb_dq % 2 != 0 || nb_sq % 2 != 0)
	{
		ft_putstr_fd("syntax error quotes\n", 2);
		g_exstat = 2;
		return (-1);
	}
	return (1);
}

int	ft_pipe_2(t_lex *lex)
{
	if (ft_strlen(lex->str) < 2)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		g_exstat = 2;
		return (-1);
	}
	else if (ft_strlen(lex->str) > 1)
	{
		ft_putstr_fd("syntax error near unexpected token `||'\n",
			2);
		g_exstat = 2;
		return (-1);
	}
	return (0);
}

int	ft_pipe_3(t_lex *lex)
{
	if (lex->next != NULL && lex->next->token == TOK_PIPE
		&& ft_strlen(lex->next->str) < 2)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	else if (lex->next != NULL && lex->next->token == TOK_PIPE
		&& ft_strlen(lex->next->str) > 1)
	{
		ft_putstr_fd("syntax error near unexpected token `||'\n",
			2);
		return (-1);
	}
	else if (lex->next == NULL)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	else if (ft_strlen(lex->str) >= 2)
	{
		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_pipe(t_lex *lex, t_lex *start)
{
	while (lex != NULL)
	{
		if (start->token == TOK_PIPE)
		{
			if (ft_pipe_2(lex) == -1)
				return (-1);
		}
		else if (start->token != TOK_PIPE && lex->token == TOK_PIPE)
		{
			if (ft_pipe_3(lex) == -1)
			{
				g_exstat = 2;
				return (-1);
			}
		}
		lex = lex->next;
	}
	return (0);
}
