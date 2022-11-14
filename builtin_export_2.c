/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:04:28 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 00:28:49 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_line_tab(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (env->next != NULL)
		{
			i++;
			env = env->next;
		}
		else
			return (i);
	}
	return (i);
}

char	**ft_malloc_cpy_env(t_env *env)
{
	char	**strs;
	int		i;

	i = 0;
	while (env != NULL)
	{
		if (env->next != NULL)
		{
			i++;
			env = env->next;
		}
		else
			break ;
	}
	strs = malloc(sizeof(char *) * (i + 2));
	if (strs == NULL)
		return (NULL);
	return (strs);
}

void	ft_copy_env_to_tab(t_env *env, char **strs)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		strs[i] = env->str;
		i++;
		if (env->next != NULL)
			env = env->next;
		else
			break ;
	}
	strs[i] = NULL;
}

int	ft_diff_tab(char *strs, char *strs2)
{
	int	i;

	i = 0;
	while (strs[i] == strs2[i] && strs[i] != '\0' && strs2[i] != '\0')
		i++;
	return (strs[i] - strs2[i]);
}

void	ft_sort_tab(char **strs)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (strs[i] != NULL || strs[i][0] != '\0')
	{
		if (strs[i + 1] == NULL)
			return ;
		if (ft_diff_tab(strs[i], strs[i + 1]) > 0)
		{
			tmp = strs[i];
			strs[i] = strs[i + 1];
			strs[i + 1] = tmp;
		}
		i++;
	}
}
