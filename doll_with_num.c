/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_with_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:23:49 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/12 20:18:06 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_alpha_num(t_lex *lex)
{
	int	i;

	i = 0;
	while ((lex->next->str[i] <= 'z' && lex->next->str[i] >= 'a')
		|| (lex->next->str[i] <= 'Z' && lex->next->str[i] >= 'A')
		|| (lex->next->str[i] <= '9' && lex->next->str[i] >= '0'))
		i++;
	return (i);
}

void	ft_cut_after_1_num(t_lex *lex)
{
	int	i;
	int	j;

	i = 1;
	j = ft_strlen(lex->next->str);
	free(lex->str);
	lex->str = malloc(sizeof(char) * j);
	if (lex->str == NULL)
		return ;
	j = 0;
	while (lex->next->str[i] != '\0')
	{
		lex->str[j] = lex->next->str[i];
		i++;
		j++;
	}
	lex->str[j] = '\0';
	lex->token = TOK_WORD;
	ft_free_after_1_num(lex);
}

void	ft_free_after_1_num(t_lex *lex)
{
	if (lex == NULL)
		return ;
	if (lex->next->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = lex->next->next;
		return ;
	}
	else if (lex->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = NULL;
		return ;
	}
}

int	ft_after_doll_is_num(t_lex *lex, t_utils *utils)
{
	if(utils->ambigous == 1)
		return (FAIL);
	if (lex->next->str[0] >= '0' && lex->next->str[0] <= '9'
		&& lex->next->str[1] == '\0')
		return (SUCCESS);
	else if (lex->next->str[0] >= '0' && lex->next->str[0] <= '9'
		&& lex->next->str[1] != '\0')
		return (SUCCESS + 1);
	else if (lex->next->str[0] == '=')
		return (SUCCESS + 2);
	return (1024);
}
