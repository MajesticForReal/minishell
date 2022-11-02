/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:32:07 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/02 15:08:29 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_parser_limiter(t_lex *tmp)
{
	int	i;
	int	j;
	int	k;
	char *str;

	str = NULL;
	i = 0;
	j = 0;
	k = 0;
	j = ft_strlen(tmp->str) - 1;
	while(tmp->str[i] != '\0')
	{
		if(tmp->str[i] == '"')
		{
			k++;
			i++;
		}
		else
			break;
	}
	printf("k = %d\n", k);
	while(j > 0)
	{
		if(tmp->str[j] == '"')
		{
			k++;
			j--;
		}
		else
			break;
	}
	printf("k = %d\n", k);
	// printf("str = %s\n", str);
	printf("tmp->str = %s\n", tmp->str);
	return(str);
}