/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:32:17 by anrechai          #+#    #+#             */
/*   Updated: 2022/10/31 18:40:06 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(t_lex *lex)
{
	t_lex	*start;

	start = lex;

	while (lex != NULL)
	{
		if (lex->token == TOK_PIPE)
		{
			if (ft_pipe(lex, start) == -1)
				return ;
		}
		else if (lex->token == TOK_IN)
		{
			if (ft_in(lex) == -1)
				return ;
		}
		else if (lex->token == TOK_OUT)
		{
			if (ft_out(lex) == -1)
				return ;
		}
		lex = lex->next;
	}
}

void	ft_tok_fromfrom(t_lex *lex)
{
	while (lex != NULL)
	{
		if (lex->str[0] == '>' && lex->str[1] == '>' && lex->str[2] == '\0')
			lex->token = TOK_FROMFROM;
		lex = lex->next;
	}
}

void	ft_tok_toto(t_lex *lex)
{
	while (lex != NULL)
	{
		if (lex->str[0] == '<' && lex->str[1] == '<' && lex->str[2] == '\0')
			lex->token = TOK_TOTO;
		lex = lex->next;
	}
}

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
		return (-1);
	}
	return (1);
}

int	ft_out(t_lex *lex)
{
	ft_tok_fromfrom(lex);
	while (lex != NULL)
	{
		if (lex->str != NULL && (lex->token == TOK_OUT
				|| lex->token == TOK_FROMFROM))
		{
			if ((lex->token == TOK_OUT || lex->token == TOK_FROMFROM)
				&& lex->next == NULL && ft_strlen(lex->str) < 3)
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (-1);
			}
			else if ((lex->token == TOK_OUT || lex->token == TOK_FROMFROM)
					&& ft_strlen(lex->str) == 3)
			{
				ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
				return (-1);
			}
			else if ((lex->token == TOK_OUT || lex->token == TOK_FROMFROM)
					&& ft_strlen(lex->str) > 3)
			{
				ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
				return (-1);
			}
			else if ((lex->token == TOK_OUT || lex->token == TOK_FROMFROM)
					&& (lex->next->token != TOK_WORD
						&& lex->next->token != TOK_DQ
						&& lex->next->token != TOK_SQ
						&& lex->next->token != TOK_DOLL))
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putchar_fd(lex->next->str[0], 2);
				ft_putchar_fd(lex->next->str[1], 2);
				ft_putstr_fd("'\n", 2);
				return (-1);
			}
		}
		lex = lex->next;
	}
	return (0);
}

int	ft_in(t_lex *lex)
{
	ft_tok_toto(lex);
	while (lex != NULL)
	{
		if (lex->str != NULL && (lex->token == TOK_IN
				|| lex->token == TOK_TOTO))
		{
			if ((lex->token == TOK_IN || lex->token == TOK_TOTO)
				&& lex->next == NULL && ft_strlen(lex->str) < 4)
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (-1);
			}
			else if ((lex->token == TOK_IN || lex->token == TOK_TOTO)
					&& ft_strlen(lex->str) == 4)
			{
				ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
				return (-1);
			}
			else if ((lex->token == TOK_IN || lex->token == TOK_TOTO)
					&& ft_strlen(lex->str) == 5)
			{
				ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
				return (-1);
			}
			else if ((lex->token == TOK_IN || lex->token == TOK_TOTO)
					&& ft_strlen(lex->str) > 5)
			{
				ft_putstr_fd("syntax error near unexpected token `<<<'\n", 2);
				return (-1);
			}
			else if ((lex->token == TOK_IN || lex->token == TOK_TOTO)
					&& (lex->next->token != TOK_WORD
						&& lex->next->token != TOK_DQ
						&& lex->next->token != TOK_SQ
						&& lex->next->token != TOK_DOLL))
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putchar_fd(lex->next->str[0], 2);
				ft_putchar_fd(lex->next->str[1], 2);
				ft_putstr_fd("'\n", 2);
				return (-1);
			}
		}
		lex = lex->next;
	}
	return (0);
}

int	ft_pipe(t_lex *lex, t_lex *start)
{
	while (lex != NULL)
	{
		if (start->token == TOK_PIPE)
		{
			if (ft_strlen(lex->str) < 2)
			{
				ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
				return (-1);
			}
			else if (ft_strlen(lex->str) > 1)
			{
				ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
				return (-1);
			}
		}
		else if (start->token != TOK_PIPE && lex->token == TOK_PIPE)
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
				ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
				return (-1);
			}
			else if (lex->next == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
				return (-1);
			}
		}
		lex = lex->next;
	}
	return (0);
}
