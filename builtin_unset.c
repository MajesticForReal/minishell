/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:28:36 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 21:52:32 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_var(t_lex *lex, t_env *env)
{
	while (ft_compare(lex->str, "unset") != SUCCESS)
		lex = lex->next;
	if (lex->next != NULL)
		lex = lex->next;
	while (env->next != NULL)
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
	if (env->next->next == NULL)
	{
		free(env->next->str);
		free(env->next);
		env->next = NULL;
	}
	else if (env->next->next != NULL)
	{
		env_to_del = env->next;
		env->next = env->next->next;
		free(env_to_del->str);
		free(env_to_del);
	}
}

int	ft_spec_case(char *input)
{
	if (input[0] == '.' && input[1] == '\0')
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		return (-1);
	}
	if (input[0] == '.' && input[1] == '.' && input[2] == '\0')
	{
		g_exstat = 127;
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		return (-1);
	}
	if (input[0] == '.' && input[1] == ' ' && input[2] == '.')
	{
		ft_putstr_fd("minishell: .: .: is a directory\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_input(char *input, t_utils *utils)
{
	if (!input)
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd("\n", 2);
		g_exstat = 0;
		ft_free_env(utils->env);
		ft_free_export(utils);
		ft_free_utils(utils);
		exit(EXIT_SUCCESS);
	}
	if (ft_spec_case(input) == -1)
		return (-1);
	return (0);
}
