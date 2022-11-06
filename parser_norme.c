/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_norme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:25:20 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/06 20:26:03 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_33(t_lex **lex)
{
	if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& ft_strlen((*lex)->str) == 4)
	{
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
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

int	ft_in_3(t_lex **lex)
{
	if (((*lex)->token == TOK_IN || (*lex)->token == TOK_TOTO)
		&& (*lex)->next == NULL && ft_strlen((*lex)->str) < 4)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			2);
		return (-1);
	}
	else if (ft_in_33(lex) == -1)
		return (-1);
	return (0);
}
