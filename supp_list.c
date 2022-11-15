/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:58:55 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 15:59:21 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_supp_2_list(t_lex *lex)
{
	t_lex *tmp;

	free(lex->str);
	lex->str = malloc(sizeof(char) * 2);
	if (lex->str == NULL)
		return ;
	lex->str[0] = ' ';
	lex->str[1] = '\0';
	lex->token = TOK_SPACE;
	if (lex->next->next != NULL)
	{
		tmp = lex->next;
		lex->next = lex->next->next;
		free(tmp->str);
		free(tmp);
		return ;
	}
	else
	{
		tmp = lex->next;
		lex->next = NULL;
		free(tmp->str);
		free(tmp);
		return ;
	}
}
