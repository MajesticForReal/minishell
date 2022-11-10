/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 21:13:40 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_var(t_lex *lex, t_env *env)
{
	if (lex->next != NULL && lex->next->token == TOK_SPACE)
		lex = lex->next;
	if(lex->next != NULL && lex->next->token == TOK_WORD)
		lex = lex->next;
	printf("retour = %d\n", ft_check_valid_export_env(lex->str));
	if (ft_check_valid_export_env(lex->str) == 1)
		ft_add_back_str(env, lex->str);
	if (ft_check_valid_export_env(lex->str) == 2)
		ft_copy_env_n_rate(env);

else
		return ;
}

void	ft_replace_t_env(t_env *env, char *str)
{
	int	i;

	if(env == NULL || str == NULL || str[0] == '\0')
		return ;
	i = ft_compare_index(env, str);
	while(i > 0)
	{
		if(env->next != NULL)
			env = env->next;
		i--;
	}
	free(env->str);
	env->str = str;
}

void	ft_add_back_str(t_env *env, char *str)
{
	t_env	*new_env;
	t_env	*env_cpy;

	env_cpy = env;
	new_env = ft_init_env();
	
	while (env_cpy != NULL )
	{
		if (ft_compare_stop_egal(env_cpy->str, str) == SUCCESS)
		{
			ft_replace_t_env(env, str);
			return ;
		}
		env_cpy = env_cpy->next;
	}
	while (env->next != NULL)
		env = env->next;
	env->next = new_env;
	new_env->str = str;
}

int	ft_compare_index(t_env *env, char *str)
{
	int	i;

	i = 0;
	while(env != NULL)
	{
		if(ft_compare_stop_egal(env->str, str) == FAIL)
			i++;
		else
			return (i);
		if(env->next != NULL)
			env = env->next;
	}
	return (-1);
}

int	ft_compare_stop_egal(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] == str2[i] && str[i] != '=' && str2[i] != '=')
	{
		if(str[i] != str2[i])
			return (FAIL);
		i++;
	}
	if(str[i] == str2[i])
		return (SUCCESS);
	else
		return (FAIL);
		
}


