/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 19:11:10 by anrechai         ###   ########.fr       */
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
	int		j;

	i = 0;
	j = 0;
	if (str != NULL)
		j = ft_strlen(str);
	env_str = malloc(sizeof(char) * (j + 1));
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

t_env	*ft_initalize_env(void)
{
	t_env	*curr;

	curr = malloc(sizeof(t_env));
	if (!curr)
		return (NULL);
	curr->next = NULL;
	curr->str = NULL;
	return (curr);
}

void	ft_add_back_str_export_first(t_env *export, char *str)
{
	t_env	*new_export;

	new_export = ft_initalize_env();
	while (export->next != NULL)
		export = export->next;
	export->next = new_export;
	new_export->str = str;
	new_export->next = NULL;
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
