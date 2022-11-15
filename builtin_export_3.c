/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:06:56 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 18:07:59 by anrechai         ###   ########.fr       */
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
	int		nb;

	nb = -1;
	i = ft_count_line_tab(env) + 2;
	strs = malloc(sizeof(char *) * (i));
	ft_copy_env_to_tab(env, strs);
	while (--i > 0)
		ft_sort_tab(strs);
	i = ft_count_line_tab(env) + 2;
	tab_export = ft_size_up_tab(strs, i, nb);
	i = 0;
	export = ft_export_list(tab_export);
	i = 0;
	free(tab_export);
	free(strs);
	return (export);
}
