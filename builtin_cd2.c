/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:03:17 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 22:18:19 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_concat(char *str_1, char *str_2)
{
	char	*path;
	int		i;
	int		k;

	i = 0;
	k = 0;
	path = malloc(sizeof(char) * ft_strlen(str_1) + ft_strlen(str_2) + 2);
	if (path == NULL)
		return (NULL);
	while (str_1[i] != '\0')
	{
		path[k] = str_1[i];
		i++;
		k++;
	}
	path[k] = '/';
	k++;
	i = -1;
	while (str_2[++i] != '\0')
	{
		path[k] = str_2[i];
		k++;
	}
	path[k] = '\0';
	return (path);
}

int	ft_builtin_path_a(char *lex_str)
{
	if(chdir(lex_str) == -1)
	{
		perror(lex_str);
		g_exstat = 1;
		return (FAIL);
	}
	return (SUCCESS);
}

int	ft_builtin_detect_path_a_r(char *lex_str)
{
	if(lex_str[0] == '/' && lex_str[1] != '\0')
		return(SUCCESS);
	else
		return (FAIL);
}

