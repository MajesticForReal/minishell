/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:06:56 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 18:47:58 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_export_list(char **strs, t_env *export)
{
	int		i;

	export = malloc(sizeof(t_env));
	if (export == NULL)
		return (NULL);
	export->next = NULL;
	export->str = strs[0];
	i = 0;
	while (strs[i] != NULL)
	{
		ft_add_back_str_export_first(export, strs[i]);
		i++;
	}
	return (export);
}

t_env	*ft_copy_env(t_env *env, t_env *export)
{
	char	**strs;
	char	**tab_export;
	int		i;
	int		nb;

	nb = -1;
	i = ft_count_line_tab(env) + 2;
	strs = malloc(sizeof(char *) * i);
	ft_copy_env_to_tab(env, strs);
	while (--i > 0)
		ft_sort_tab(strs);
	i = ft_count_line_tab(env) + 2;
	tab_export = NULL;
	tab_export = ft_size_up_tab(strs, i, nb, tab_export);
	i = 0;
	export = ft_export_list(tab_export, export);
	i = 0;
	while(tab_export[i])
	{
		free(tab_export[i]);
		i++;
	}
	free(tab_export);
	free(strs);
	return (export);
}

