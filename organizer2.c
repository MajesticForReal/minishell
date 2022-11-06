/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:16:59 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/06 21:17:27 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_organizer_heredoc(char *input, int fd)
{
	ft_dollar_heredoc(input, fd);
}

void	ft_organizer(t_lex **lex)
{
	ft_clear_quotes(lex);
	ft_concat_clear(lex);
}

void	ft_print_list(t_lex *lex)
{
	while (lex->str != NULL && lex->next != NULL)
	{
		printf("%s\n", lex->str);
		lex = lex->next;
	}
	if (lex->str != NULL)
		printf("%s\n", lex->str);
}

t_lex	*ft_initialize_struct2(char *str1, char *str2, t_lex *next)
{
	t_lex	*new;

	new = malloc(sizeof(t_lex));
	if (!new)
		return (NULL);
	new->next = next;
	new->token = 9;
	new->str = ft_concat2(str1, str2);
	return (new);
}
