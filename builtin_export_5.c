/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:00:02 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 17:55:22 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_var(t_lex *lex, t_exec *exec, t_utils *utils)
{
	while (ft_compare(lex->str, "export") != SUCCESS)
		lex = lex->next;
	if (lex->next == NULL || (lex->next->token == TOK_SPACE
			&& lex->next->next == NULL) || (lex->next->token == TOK_SPACE
			&& lex->next->next->token != TOK_WORD))
	{
		ft_print_list_export(utils->export, exec, utils);
		return ;
	}
	if (lex->next != NULL && lex->next->token == TOK_SPACE)
		lex = lex->next;
	if (lex->next != NULL && lex->next->token == TOK_WORD)
		lex = lex->next;
	if (ft_check_valid_export_env(lex->str) == 1)
	{
		ft_add_back_str(utils->env, lex->str);
		ft_add_back_str_export(utils->export, lex->str);
	}
	if (ft_check_valid_export_env(lex->str) == 2)
		ft_add_back_str_export(utils->export, lex->str);
	else
		return ;
}

void	ft_replace_t_export_1(t_env *export, char *env_str, int *i)
{
	if (export == NULL || env_str == NULL || env_str[0] == '\0')
		return ;
	*i = ft_strlen(env_str) + 3;
	export->str = malloc(sizeof(char) * (*i));
	if (export->str == NULL)
		return ;
	*i = 0;
}

void	ft_replace_t_export_2(t_env *export, int *i, int *j, int *trigger)
{
	*j = *j + 1;
	export->str[*j] = '"';
	*j = *j + 1;
	*i = *i + 1;
	*trigger = *trigger + 1;
}

void	ft_replace_t_export_3(int *i, int *j)
{
	*j = *j + 1;
	*i = *i + 1;
}

void	ft_replace_t_export(t_env *export, char *env_str)
{
	int	i;
	int	j;
	int	trigger;

	free(export->str);
	ft_replace_t_export_1(export, env_str, &i);
	trigger = 0;
	j = 0;
	while (env_str[i] != '\0')
	{
		export->str[j] = env_str[i];
		if (env_str[i] == '=' && trigger == 0 && env_str[i + 1] != '"')
			ft_replace_t_export_2(export, &i, &j, &trigger);
		else
			ft_replace_t_export_3(&i, &j);
	}
	if (env_str[i - 1] != '"')
	{
		export->str[j] = '"';
		export->str[j + 1] = '\0';
	}
	else
		export->str[j] = '\0';
}
