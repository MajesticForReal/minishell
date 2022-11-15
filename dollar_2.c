/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:57:02 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 17:59:08 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_concat_no_expand2(t_lex **lex, char *tmp)
{
	while ((*lex)->token != TOK_DOLL)
	{
		if ((*lex)->next != NULL)
			(*lex) = (*lex)->next;
		else
			break ;
	}
	(*lex)->token = TOK_WORD;
	if ((*lex)->next != NULL)
	{
		tmp = (*lex)->next->str;
		free((*lex)->str);
	}
	else
		return (NULL);
	return (tmp);
}

void	ft_concat_no_expand(t_lex *lex)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	tmp = NULL;
	tmp = ft_concat_no_expand2(&lex, tmp);
	if (tmp == NULL)
		return ;
	lex->str = malloc(sizeof(char) * ft_strlen(tmp) + 2);
	if (lex->str == NULL)
		return ;
	lex->str[0] = '$';
	while (tmp[i] != '\0')
	{
		lex->str[j] = tmp[i];
		j++;
		i++;
	}
	lex->str[j] = '\0';
	ft_free_concat_no_expand(&lex);
}

void	ft_free_concat_no_expand(t_lex **lex)
{
	t_lex	*t_tmp;

	if ((*lex)->next->next != NULL)
	{
		t_tmp = (*lex)->next;
		(*lex)->next = (*lex)->next->next;
		free(t_tmp->str);
		free(t_tmp);
	}
	else
	{
		t_tmp = (*lex)->next;
		(*lex)->next = NULL;
		free(t_tmp);
	}
}

void	ft_detect_ambigous2(t_lex *lex, t_utils *utils)
{
	if ((lex->token == TOK_OUT || (lex->token == TOK_IN && lex->str[1] == '\0')
			|| lex->token == TOK_FROMFROM) && (lex->next != NULL
			&& lex->next->token == TOK_DOLL))
	{
		if (ft_compare_just_a_part_2(lex->next->next->str) == FAIL
			&& (lex->str[1] == '\0' || (lex->str[1] == '>'
					&& lex->str[2] == '\0')))
		{
			utils->ambigous = 1;
		}
	}
}

void	ft_detect_ambigous(t_lex *lex, t_utils *utils)
{
	if ((lex->token == TOK_OUT || (lex->token == TOK_IN && lex->str[1] == '\0')
			|| lex->token == TOK_FROMFROM) && (lex->next != NULL
			&& lex->next->token == TOK_SPACE && lex->next->next != NULL
			&& lex->next->next->token == TOK_DOLL))
	{
		if (ft_compare_just_a_part_2(lex->next->next->next->str) == FAIL
			&& (lex->str[1] == '\0' || (lex->str[1] == '>'
					&& lex->str[2] == '\0')))
		{
			utils->ambigous = 1;
		}
	}
}
