/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/17 17:40:17 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_var(char *input, t_env *env)
{
	char *short_input;
	int	i;
	int	j;
	
	i = 7;
	j = 0;
	short_input = NULL;
	short_input =  malloc(sizeof(char) * ft_strlen(input) - 5);
	if (short_input == NULL)
		return ;
	
	while(input[i] != '\0')
	{
		short_input[j] = input[i];
		i++;
		j++;
	}
	short_input[j] = '\0';
	ft_add_back_str(env, short_input);
}

void	ft_add_back_str(t_env *env, char *str)
{
	t_env	*new_env;
	t_env	*env_cpy;
	
	env_cpy = env;
	new_env = ft_init_env();
	while(env_cpy != NULL)
	{
		if(ft_compare(env_cpy->str, str) == SUCCESS)
			return ;
		env_cpy = env_cpy->next;
	}
	while(env->next != NULL)
		env = env->next;
	env->next = new_env;
	new_env->str = str;
}
