/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:24:58 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 01:53:57 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_k(t_lex *lex, t_env *env, t_utils *utils)
{
	if (lex->str == NULL || lex->str[0] == '\0')
		return (FAIL);
	if (ft_check_quotes(lex) == 0)
	{
		if (ft_parser_doll(lex, env, utils) == FAIL)
			return (FAIL);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

int	ft_test_access(char *lex_str)
{
	char	**path;
	char	*new_path;
	int		i;
	int		j;

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
		{
			free(path);
			return (SUCCESS);
		}
		i++;
	}
	free(path);
	return (j);
}

int	ft_parser_doll(t_lex *lex, t_env *env, t_utils *utils)
{
	while (lex != NULL)
	{
		ft_detect_ambigous(lex, utils);
		ft_detect_ambigous2(lex, utils);
		if ((lex->token == TOK_IN && lex->str[1] == '<' && lex->next != NULL
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
