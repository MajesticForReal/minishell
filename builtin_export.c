/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/06 20:36:08 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_valid_export(char *lex_str)
{
	int	i;

	i = 0;
	while (lex_str[i] != '\0')
	{
		if (lex_str[i] == '=')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

void	ft_export_var(t_lex *lex, t_env *env)
{
	if (lex->next != NULL)
		lex = lex->next;
	if (ft_check_valid_export(lex->str) == SUCCESS)
		ft_add_back_str(env, lex->str);
	else
		return ;
}

void	ft_add_back_str(t_env *env, char *str)
{
	t_env	*new_env;
	t_env	*env_cpy;

	env_cpy = env;
	new_env = ft_init_env();
	while (env_cpy != NULL)
	{
		if (ft_compare(env_cpy->str, str) == SUCCESS)
			return ;
		env_cpy = env_cpy->next;
	}
	while (env->next != NULL)
		env = env->next;
	env->next = new_env;
	new_env->str = str;
}

int	ft_builtin_cd_rac(void)
{
	if (chdir("/") == -1)
	{
		perror("chdir()");
		return (FAIL);
	}
	return (SUCCESS);
}
