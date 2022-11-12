/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:24:58 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/12 22:05:24 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_k(t_lex *lex, t_env *env, t_utils *utils)
{
	if (lex->str == NULL || lex->str[0] == '\0')
		return (FAIL);
	if (ft_check_quotes(lex) == 0)
	{
		if(ft_parser_doll(lex, env, utils) == FAIL)
			return(FAIL);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

void	ft_concat_no_expand(t_lex *lex)
{
	char *tmp;
	int	i;
	int	j;
	t_lex *t_tmp;
	
	
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
	lex->str[j] = '\0';
	if(lex->next->next != NULL)
	{
		t_tmp = lex->next;
		lex->next = lex->next->next;
		free(t_tmp->str);
		free(t_tmp);
	}
	else
	{
		t_tmp = lex->next;
		lex->next = NULL;
		free(t_tmp);
	}
	(void)t_tmp;
}

int	ft_test_access(char *lex_str)
{
	char **path;
	char *new_path;
	int	i;
	int	j;

	
	path = ft_split(getenv("PATH"), ':');
	i = 0;
	j = 0;
	while (path && path[i])
	{
		new_path = NULL;
		new_path = ft_strcat_path(path[i], lex_str);
		if (new_path == NULL)
			return (FAIL);
		if (access(new_path, X_OK) == FAIL)
			j = FAIL;
		else
			return (SUCCESS);
			
		i++;
	}
	return(j);	
}

int	ft_parser_doll(t_lex *lex, t_env *env, t_utils *utils)
{
	int	i;

	i = 0;
	while (lex != NULL)
	{
		
		if((lex->token == TOK_OUT || (lex->token == TOK_IN && lex->str[1] == '\0') || lex->token == TOK_FROMFROM)
			&& (lex->next != NULL
			&& lex->next->token == TOK_SPACE
			&& lex->next->next != NULL
			&& lex->next->next->token == TOK_DOLL))
			if(ft_compare_just_a_part_2(lex->next->next->next->str) == FAIL && (lex->str[1] == '\0' || lex->str[1] == '>') && lex->str[2] == '\0')
				utils->ambigous = 1;
		if((lex->token == TOK_OUT || (lex->token == TOK_IN && lex->str[1] == '\0') || lex->token == TOK_FROMFROM)
			&& (lex->next != NULL && lex->next->token == TOK_DOLL))
			if(ft_compare_just_a_part_2(lex->next->next->str) == FAIL && (lex->str[1] == '\0' || lex->str[1] == '>') && lex->str[2] == '\0')
				utils->ambigous = 1;
		if((lex->token == TOK_IN && lex->str[1] == '<' && lex->next != NULL
			&& lex->next->token == TOK_SPACE && lex->next->next != NULL
			&& lex->next->next->token == TOK_DOLL) || (lex->token == TOK_IN
			&& lex->str[1] == '<' && lex->next != NULL
			&& lex->next->token == TOK_DOLL))
			ft_concat_no_expand(lex->next);
		if (lex->token == TOK_DOLL)
			ft_dollar(lex, env, utils);
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	return (SUCCESS);
	(void)i;
	(void)env;
}

void	ft_dollar(t_lex *lex, t_env *env, t_utils *utils)
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
	ft_dollar_2(lex, env, utils);
}

void	ft_dollar_2(t_lex *lex, t_env *env, t_utils *utils)
{
	if (ft_doll_interogation(lex) == SUCCESS)
		ft_change_doll_to_exit(lex);
	else if (ft_compare_just_a_part_2(lex->next->str) == SUCCESS)
		ft_change_list_to_var(lex);
	else if (ft_after_doll_is_num(lex, utils) == SUCCESS)
	{
		ft_supp_2_list(lex);
		return ;
	}
	else if (ft_after_doll_is_num(lex, utils) == SUCCESS + 1)
		ft_cut_after_1_num(lex);
	else if (ft_after_doll_is_num(lex, utils) == SUCCESS + 2)
		ft_change_doll_egal(lex);
	else if (ft_shearch_var(lex->next->str, env) == FAIL
		&& ft_shearch_special_char(lex) == FAIL && utils->ambigous != 1)
		ft_supp_2_list(lex);
	else if (ft_shearch_var(lex->next->str, env) == FAIL
		&& ft_shearch_special_char(lex) == FAIL && utils->ambigous != 1)
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