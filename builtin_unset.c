/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:28:36 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/17 18:41:57 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_var(char *input, t_env *env)
{
	char *short_input;
	int	i;
	int	j;
	
	i = 6;
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
	while(env->next != NULL)
	{
		if (ft_compare(env->next->str, short_input) == SUCCESS)
		{
			ft_del_struct(env);
			return ;
		}
		env = env->next;
	}
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