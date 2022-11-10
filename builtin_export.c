/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:02 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 22:12:19 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_rate_str(t_env *env, int	last_rate)
{
	int	i;
	int	rate;
	int	min_rate;


	i = 0;
	rate = 0;
	min_rate = 2147483646;
	while(env != NULL)
	{
		while(env->str[i] != '\0' && env->str[i] != '=')
		{
			rate = rate + env->str[i];
			i++;
		}
		i = 0;
		if(rate <= min_rate && rate >= last_rate)
		{
			min_rate = rate;
		}
		rate = 0;
		if(env->next != NULL)
			env = env->next;
		else
			return (min_rate);
	}
	return(2);
}

void	ft_copy_env_n_rate(t_env *env)
{
	// int	last_rating;
// 
	// last_rating = 0;
	(void)env;
}