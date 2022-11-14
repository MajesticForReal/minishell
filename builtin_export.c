/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:02 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 00:42:53 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_size_up_tab_2(char **strs, int *i)
{
	char	**export;
	int		j;

	j = 0;
	export = malloc(sizeof(char *) * *i);
	if (export == NULL)
		return (NULL);
	*i = 0;
	while (strs[j] != NULL)
	{
		*i = (ft_strlen(strs[j]) + 3);
		export[j] = malloc(sizeof(char) * ((*i) + 1));
		if (export[j] == NULL)
			return (NULL);
		j++;
	}
	*i = 0;
	return (export);
}

void	ft_size_up_tab_3(int *k, int *i, int *j, char **export)
{
	export[*i][*j] = '"';
	*j = *j + 1;
	export[*i][*j] = '\0';
	*j = 0;
	*k = 0;
	*i = *i + 1;
}

char	ft_size_up_tab_4(int *i, int *j, int *k, char **strs)
{
	char	c;

	c = strs[*i][*k];
	*j = *j + 1;
	*k = *k + 1;
	return (c);
}

char	**ft_size_up_tab(char **strs, int i)
{
	char **export;
	int j;
	int k;

	j = 0;
	k = 0;
	export = ft_size_up_tab_2(strs, &i);
	i = 0;
	while (strs[i] != NULL)
	{
		while (strs[i][k] != '\0')
		{
			if (strs[i][k] == '=')
			{
				export[i][j] = strs[i][k];
				j++;
				export[i][j] = '"';
				j++;
				k++;
			}
			else
				export[i][j] = ft_size_up_tab_4(&i, &j, &k, strs);
		}
		ft_size_up_tab_3(&k, &i, &j, export);
	}
	export[i] = NULL;
	return (export);
}