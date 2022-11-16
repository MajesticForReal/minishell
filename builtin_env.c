/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 00:28:40 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_t_env(t_env *env, char *env_str)
{
	if (env == NULL || env_str == NULL || env_str[0] == '\0')
		return ;
	free(env->str);
	env->str = env_str;
}

char	*ft_copy_lex_str(char *str)
{
	char	*env_str;
	int		i;

	i = 0;
	env_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (env_str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		env_str[i] = str[i];
		i++;
	}
	env_str[i] = '\0';
	return (env_str);
}

void	ft_add_back_str_export_first(t_env *export, char *str)
{
	t_env	*new_export;
	char	*export_str;

	export_str = ft_copy_lex_str(str);
	new_export = ft_init_env();
	while (export->next != NULL)
		export = export->next;
	export->next = new_export;
	new_export->str = export_str;
}

void	ft_add_back_str(t_env *env, char *str)
{
	t_env	*new_env;
	t_env	*env_cpy;
	char	*env_str;

	env_str = ft_copy_lex_str(str);
	env_cpy = env;
	new_env = ft_init_env();
	while (env_cpy != NULL)
	{
		if (ft_compare_stop_egal(env_cpy->str, env_str) == SUCCESS)
		{
			ft_replace_t_env(env_cpy, env_str);
			env = env_cpy;
			return ;
		}
		env_cpy = env_cpy->next;
	}
	while (env->next != NULL)
		env = env->next;
	env->next = new_env;
	new_env->str = env_str;
}

int	ft_compare_index(t_env *env, char *str)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (ft_compare_stop_egal(env->str, str) == FAIL)
			i++;
		else
			return (i);
		if (env->next != NULL)
			env = env->next;
	}
	return (-1);
}
