/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:22:06 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 16:42:40 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_doll_interogation(t_lex *lex)
{
	if (lex->token == 8 && lex->next->token == 9
		&& lex->next->str[0] == '?'
		&& lex->next->str[1] == '\0')
		return (SUCCESS);
	else
		return (FAIL);
}

void	ft_change_doll_to_exit(t_lex *lex)
{
	t_lex	*tmp;

	free (lex->str);
	lex->token = 9;
	lex->str = ft_itoa(g_exstat);
	if (lex->next->next != NULL)
	{
		tmp = lex->next;
		lex->next = lex->next->next;
		free (tmp->str);
		free (tmp);
	}
	else
	{
		tmp = lex->next;
		lex->next = NULL;
		free (tmp);
	}
	(void)tmp;
}
