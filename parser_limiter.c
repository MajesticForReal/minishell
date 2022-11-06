/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:32:07 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/06 20:49:29 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parser_limiter(t_lex *tmp)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	str = NULL;
	i = -1;
	k = 0;
	j = ft_strlen(tmp->str);
	while (tmp->str[++i] != '\0')
	{
		if (tmp->str[i] == '"')
			k++;
		else
			break ;
	}
	while (--j > 0)
	{
		if (tmp->str[j] == '"')
			k++;
		else
			break ;
	}
	return (str);
}
