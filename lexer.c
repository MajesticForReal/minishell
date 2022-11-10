/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:18:43 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/10 22:14:43 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first_lex_token(t_lex *lex, char *input, int i)
{
	if (input[i] == '<')
		lex->token = TOK_IN;
	else if (input[i] == '>')
		lex->token = TOK_OUT;
	else if (input[i] == 34)
		lex->token = TOK_DQ;
	else if (input[i] == 36)
		lex->token = TOK_DOLL;
	else if (input[i] == 39)
		lex->token = TOK_SQ;
	else if (input[i] == '|')
		lex->token = TOK_PIPE;
	return ;
}

int	ft_first_lex_concat(t_lex *lex, char *input, int i, int size)
{
	int	j;

	j = 0;
	lex->str = malloc(sizeof(char) * (size + 1));
	if (!lex->str)
		return (0);
	lex->str = NULL;
	j = 0;
	if (input[0] != '\0')
	{
		while (j < size)
		{
			lex->str[j] = input[i];
			i++;
			j++;
		}
		lex->str[j] = '\0';
		lex->next = NULL;
	}
	return (i);
}

int	ft_first_lex(t_lex *lex, char *input)
{
	int	i;
	int	size;

	i = 0;
	while (input[i] != '\0' && (input[i] == ' ' || input[i] == '\t'))
	{
		lex->token = TOK_SPACE;
		i++;
	}
	if (input[i] == '<' || input[i] == '>' || input[i] == 34 || input[i] == 36
		|| input[i] == 39 || input[i] == '|')
		ft_first_lex_token(lex, input, i);
	else if (input[i] != '|' && input[i] != 34 && input[i] != 36
			&& input[i] != 39 && input[i] != '<' && input[i] != '>'
			&& input[i] != ' ' && input[i] != '\t' && input[i] != '\0')
	{
		i = ft_word(input, lex, i);
		return (i);
	}
	size = ft_size_str(input, i, input[i]);
	return (ft_first_lex_concat(lex, input, i, size));
}

void	ft_lexer(char *input, t_lex *lex)
{
	int	i;
	
	i = ft_first_lex(lex, input);
	while (input[i])
	{
		if (input[i] != '|' && input[i] != 34 && input[i] != 36
			&& input[i] != 39 && input[i] != '<' && input[i] != '>'
			&& input[i] != ' ' && input[i] != '\t')
			i = add_back(lex, TOK_WORD, input, i);
		else if (input[i] == ' ' || input[i] == '\t')
			i = add_back(lex, TOK_SPACE, input, i);
		else if (input[i] == '<')
			i = add_back(lex, TOK_IN, input, i);
		else if (input[i] == '>')
			i = add_back(lex, TOK_OUT, input, i);
		else if (input[i] == 34)
			i = add_back(lex, TOK_DQ, input, i);
		else if (input[i] == 36)
			i = add_back(lex, TOK_DOLL, input, i);
		else if (input[i] == 39)
			i = add_back(lex, TOK_SQ, input, i);
		else if (input[i] == '|')
			i = add_back(lex, TOK_PIPE, input, i);
	}
	i = 0;
}
