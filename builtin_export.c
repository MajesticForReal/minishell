/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:02 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/11 19:48:52 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_count_line_tab(t_env *env)
{
	int	i;
	
	i = 0;
	while(env != NULL)
	{
		if(env->next != NULL)
		{
			i++;
			env = env->next;
		}
		else
			return (i);
	}
	return(i);
}

char	**ft_malloc_cpy_env(t_env *env)
{
	char **strs;
	int	i;
	
	i = 0;
	while(env != NULL)
	{
		if(env->next != NULL)
		{
			i++;
			env = env->next;
		}
		else
			break ;
	}
	strs = malloc(sizeof(char *) * (i + 2));
	if(strs == NULL)
		return (NULL);
	return (strs);
}

void	ft_copy_env_to_tab(t_env *env, char **strs)
{
	int	i;

	i = 0;
	while(env != NULL)
	{
		strs[i] = env->str;
		i++;
		if(env->next != NULL)
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
	while(strs[i] == strs2[i] && strs[i] != '\0' && strs2[i] != '\0')
		i++;
	return (strs[i] - strs2[i]);
}

void	ft_sort_tab(char **strs)
{
	int	i;
	char *tmp;

	tmp = NULL;
	i = 0;
	while(strs[i] != NULL || strs[i][0] != '\0')
	{
		if(strs[i + 1] == NULL)
			return ;
		if(ft_diff_tab(strs[i], strs[i + 1]) > 0)
		{
			tmp = strs[i];
			strs[i] = strs[i + 1];
			strs[i + 1] = tmp;
		}
		i++;
	}
}

char	**ft_size_up_tab(char **strs, int i)
{
	char **export;
	int	j;
	int	k;

	j = 0;
	export = malloc(sizeof(char *) * i);
	if(export == NULL)
		return (NULL);
	i = 0;
	while(strs[j] != NULL)
	{
		k = ft_strlen(strs[j]);
		i = ft_strlen(strs[j]) + 2;
		export[j] = malloc(sizeof(char *) * i);
		if(export[j] == NULL)
			return (NULL);
		j++;
	}
	j = 0;
	i = 0;
	k = 0;
	
	while(strs[i] != NULL)
	{
		while(strs[i][k] != '\0')
		{
			if(strs[i][k] == '=')
			{
				export[i][j] = strs[i][k];
				j++;
				export[i][j] = '"';
				j++;
				k++;
			}
			else
			{
				export[i][j] = strs[i][k];
				j++;
				k++;
			}
		}
		export[i][j] = '"';
		export[i][j + 1] = '\0';
		k = 0;
		j = 0;
		i++;
	}
	export[i] = NULL;
	return (export);
	
}

t_env	*ft_export_list(char **strs)
{
	int	i;
	t_env *export;

	i = 1;
	export = malloc(sizeof(t_env));
	if(export == NULL)
		return (NULL);
	export->str = strs[0];
	export->next = NULL;
	while(strs[i] != NULL)
	{
		ft_add_back_export(export, strs[i]);
		i++;
	}
	return(export);
}


void	ft_add_back_export(t_env *export, char *strs)
{
	if(export == NULL)
		return ;
	t_env *new;
	new = malloc(sizeof(t_env));
	if(new == NULL)
		return ;
	while(export != NULL)
	{
		if(export->next != NULL)
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
	char **strs;
	t_env *export;
	char **tab_export;
	int	i;
	
	i = ft_count_line_tab(env) + 2;
	strs = malloc(sizeof(char *) * (i));
	ft_copy_env_to_tab(env, strs);
	while(--i > 0)
		ft_sort_tab(strs);
	i = ft_count_line_tab(env) + 2;
	tab_export = ft_size_up_tab(strs, i);
	i = 0;
	export = ft_export_list(tab_export);
	return(export);
	(void)export;
}

