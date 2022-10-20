/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:28:36 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/19 17:24:44 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_var(t_lex *lex, t_env *env)
{
	if(lex->next != NULL)
		lex = lex->next;
	while(env->next != NULL)
	{
		if (ft_find_variable_in_env(env->next->str, lex->str) == SUCCESS)
		{
			ft_del_struct(env);
			return ;
		}
		env = env->next;
	}
	(void)env;
}
	
int	ft_find_variable_in_env(char *var_env, char *lex_str)
{
	int	i;
	int	j;
	
	j = 0;
	i = ft_strlen(lex_str);
	while(var_env[j] != '\0' && j < i)
	{
		if(var_env[j] == lex_str[j])
			j++;
		else
			return (FAIL);
	}
	if(var_env[j] == '=')
		return (SUCCESS);
	return (FAIL);
}

void	ft_del_struct(t_env *env)
{
	t_env *env_to_del;
	
	if(env == NULL)
		return ;
	if(env->next->next == NULL)
	{
		free(env->next->str);
		free(env->next);
		env->next = NULL;
	}
	else if(env->next->next != NULL)
	{
		env_to_del = env->next;
		env->next = env->next->next;
		free(env_to_del->str);
		free(env_to_del);
	}
}