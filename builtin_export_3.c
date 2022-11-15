/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:06:56 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 15:29:28 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_export_list(char **strs)
{
	int		i;
	t_env	*export;

	i = 1;
	export = NULL;
	export = malloc(sizeof(t_env));
	if (export == NULL)
		return (NULL);
	export->str = strs[0];
	export->next = NULL;
	while (strs[i] != NULL)
	{
		ft_add_back_export(export, strs[i]);
		i++;
	}
	return (export);
}

void	ft_add_back_export(t_env *export, char *strs)
{
	t_env	*new;

	if (export == NULL)
		return ;
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return ;
	while (export != NULL)
	{
		if (export->next != NULL)
			export = export->next;
		else
			break ;
	}
	new->str = strs;
	export->next = new;
	new->next = NULL;
}

t_env	*ft_copy_env(t_env *env)
{
	char	**strs;
	t_env	*export;
	char	**tab_export;
	int		i;

	i = ft_count_line_tab(env) + 2;
	strs = malloc(sizeof(char *) * (i));
	ft_copy_env_to_tab(env, strs);
	while (--i > 0)
		ft_sort_tab(strs);
	i = ft_count_line_tab(env) + 2;
	tab_export = ft_size_up_tab(strs, i);
	i = 0;
	export = ft_export_list(tab_export);
	i = 0;
	free(tab_export);
	free(strs);
	return (export);
}

// char	**ft_size_up_tab(char **strs, int i)
// {
// char **export;
// int	j;
// int	k;
//
// j = 0;
// utils->export = malloc(sizeof(char *) * i);
// if(utils->export == NULL)
// return (NULL);
// i = 0;
// while(strs[j] != NULL)
// {
// k = ft_strlen(strs[j]);
// i = ft_strlen(strs[j]) + 2;
// export[j] = malloc(sizeof(char *) * i);
// if(export[j] == NULL)
// return (NULL);
// j++;
// }
// j = 0;
// i = 0;
// k = 0;
// while(strs[i] != NULL)
// {
// while(strs[i][k] != '\0')
// {
// if(strs[i][k] == '=')
// {
// export[i][j] = strs[i][k];
// j++;
// export[i][j] = '"';
// j++;
// k++;
// }
// else
// {
// export[i][j] = strs[i][k];
// j++;
// k++;
// }
// }
// export[i][j] = '"';
// export[i][j + 1] = '\0';
// k = 0;
// j = 0;
// i++;
// }
// export[i] = NULL;
// return (export);
//
// }