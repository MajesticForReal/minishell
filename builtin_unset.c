/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:28:36 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 01:26:19 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_var(t_lex *lex, t_env *env)
{
	while (ft_compare(lex->str, "unset") != SUCCESS)
		lex = lex->next;
	if (lex->next != NULL)
		lex = lex->next;
	while (lex != NULL && lex->token != TOK_WORD)
		lex = lex->next;
	//erreur
	while (env->next != NULL)
	{
		if (ft_find_variable_in_env(env->next->str, lex->str) == SUCCESS)
		{
			ft_del_struct(env);
			return ;
		}
		if (env->next != NULL)
			env = env->next;
		else
			break ;
	}
	(void)env;
}

int	ft_find_variable_in_env(char *var_env, char *lex_str)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(lex_str);
	while (var_env[j] != '\0' && j < i)
	{
		if (var_env[j] == lex_str[j])
			j++;
		else
			return (FAIL);
	}
	if (var_env[j] == '=')
		return (SUCCESS);
	return (FAIL);
}

void	ft_del_struct(t_env *env)
{
	t_env	*env_to_del;

	if (env == NULL)
		return ;
	env_to_del = env;
	if (env_to_del->next != NULL)
	{
		env_to_del = env->next;
		env->next = env->next->next;
		free(env_to_del->str);
		free(env_to_del);
	}
	else
	{
		env_to_del = env->next;
		env->next = NULL;
		free(env->str);
		free(env);
	}
}
