/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:24:58 by klaurier          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/11 21:57:01 by klaurier         ###   ########.fr       */
=======
/*   Updated: 2022/11/11 17:53:07 by anrechai         ###   ########.fr       */
>>>>>>> dab90028671da72fa7a8909efaf280db05bac059
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_k(t_lex *lex, t_env *env)
{
	if (lex->str == NULL || lex->str[0] == '\0')
		return (-1);
	if (ft_check_quotes(lex) == 0)
		ft_parser_doll(lex, env);
	else
		return (-1);
	return (0);
}

void	ft_concat_no_expand(t_lex *lex)
{
	printf("salut\n");
	char *tmp;
	int	i;
	int	j;

	i = 0;
	j = 1;
	while(lex->token != TOK_DOLL)
	{
		if(lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	lex->token = TOK_WORD;
	if(lex->next != NULL)
	{
		tmp = lex->next->str;
		free(lex->str);
	}	
	else
		return ;
	lex->str = malloc(sizeof(char) * ft_strlen(tmp) + 2);
	if(lex->str == NULL)
		return ;
	lex->str[0] = '$';
	while(tmp[i] != '\0')
	{
		lex->str[j] = tmp[i];
		j++;
		i++;
	}
	free(lex->next);
	lex->str[j] = '\0';
	lex->next = NULL;
	printf("lex->str = %s", lex->str);
}

void	ft_parser_doll(t_lex *lex, t_env *env)
{
	int	i;

	i = 0;
	while (lex != NULL)
	{
		if((lex->token == TOK_IN && lex->str[1] == '<' && lex->next != NULL
		&& lex->next->token == TOK_SPACE && lex->next->next != NULL
		&& lex->next->next->token == TOK_DOLL) || (lex->token = TOK_IN
		&& lex->str[1] == '<' && lex->next != NULL
		&& lex->next->token == TOK_DOLL))
		{
			ft_print_lex_k(lex);
			ft_concat_no_expand(lex->next);
			ft_print_lex_k(lex);
		}
		if(i == 1)
		{
			if(lex->next != NULL)
				lex = lex->next;
			else
				break ;
		}
		if (lex->token == TOK_DOLL)
			ft_dollar(lex, env);
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
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
