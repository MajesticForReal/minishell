/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_special_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:19:15 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 21:26:54 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cut_after_special_char(t_lex *lex)
{
	int	i;

	i = 0;
	free(lex->str);
	while (lex->next->str[i] != '\0')
	{
		if (lex->next->str[i] >= 'a' && lex->next->str[i] <= 'z')
			i++;
		else if (lex->next->str[i] >= 'A' && lex->next->str[i] <= 'Z')
			i++;
		else if (lex->next->str[i] >= '0' && lex->next->str[i] <= '9')
			i++;
		else if (lex->next->str[i] == '_')
			i++;
		else
			break ;
	}
	ft_cut_after_special_char2(lex, i);
}

void	ft_cut_after_special_char2(t_lex *lex, int i)
{
	int	j;
	int	k;

	j = 0;
	k = i;
	i--;
	while (lex->next->str[++i] != '\0')
		j++;
	lex->str = malloc(sizeof(char) * (j + 1));
	if (lex->str == NULL)
		return ;
	i = 0;
	while (lex->next->str[k] != '\0')
	{
		lex->str[i] = lex->next->str[k];
		i++;
		k++;
	}
	lex->str[i] = '\0';
	lex->token = 9;
	ft_free_after_special_char2(lex);
}

void	ft_free_after_special_char2(t_lex *lex)
{
	t_lex	*tmp;

	if (lex == NULL)
		return ;
	if (lex->next->next != NULL)
	{
		tmp = lex->next;
		lex->next = lex->next->next;
		free(tmp->str);
		free(tmp);
	}
	else
	{
		tmp = lex->next;
		lex->next = NULL;
		free(tmp->str);
		free(tmp);
	}
}

int	ft_shearch_special_char(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex->next->str[i] != '\0')
	{
		if (lex->next->str[i] >= 'a' && lex->next->str[i] <= 'z')
			i++;
		else if (lex->next->str[i] >= 'A' && lex->next->str[i] <= 'Z')
			i++;
		else if (lex->next->str[i] >= '0' && lex->next->str[i] <= '9')
			i++;
		else if (lex->next->str[i] == '_' || lex->next->str[i] == ' ')
			i++;
		else
			return (SUCCESS);
	}
	return (FAIL);
}
