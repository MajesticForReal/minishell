/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:24:58 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 00:11:28 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_k(t_lex *lex, t_env *env)
{
	if (ft_check_quotes(lex) == 0)
		ft_parser_doll(lex, env);
	else
		return (-1);
	return (0);
}

void	ft_parser_doll(t_lex *lex, t_env *env)
{
	int	i;

	i = 0;
	while (lex != NULL)
	{
		if (lex->token == TOK_DOLL)
			ft_dollar(lex, env);
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
		i++;
	}
	(void)i;
	(void)env;
}

void	ft_dollar(t_lex *lex, t_env *env)
{
	if (lex->str[0] == '$' && lex->str[1] == '$')
	{
		lex->token = 9;
		return ;
	}
	else if (lex->str[0] == '$' && lex->next == NULL)
	{
		lex->token = 9;
		return ;
	}
	else if (lex->token == 8 && lex->next->token == 2)
	{
		lex->token = 9;
		return ;
	}
	ft_dollar_2(lex, env);
}

void	ft_dollar_2(t_lex *lex, t_env *env)
{
	if (ft_doll_interogation(lex) == SUCCESS)
		ft_change_doll_to_exit(lex);
	else if (ft_compare_just_a_part_2(lex->next->str) == SUCCESS)
		ft_change_list_to_var(lex);
	else if (ft_after_doll_is_num(lex) == SUCCESS)
	{
		ft_supp_2_list(lex);
		return ;
	}
	else if (ft_after_doll_is_num(lex) == SUCCESS + 1)
		ft_cut_after_1_num(lex);
	else if (ft_after_doll_is_num(lex) == SUCCESS + 2)
		ft_change_doll_egal(lex);
	else if (ft_shearch_var(lex->next->str, env) == FAIL
		&& ft_shearch_special_char(lex) == FAIL)
		ft_supp_2_list(lex);
	else if (ft_shearch_var(lex->next->str, env) == FAIL
		&& ft_shearch_special_char(lex) == FAIL)
		ft_supp_2_list(lex);
	else if (ft_shearch_special_char(lex) == SUCCESS)
		ft_cut_after_special_char(lex);
	(void)env;
}

void	ft_supp_2_list(t_lex *lex)
{
	t_lex	*tmp;

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
