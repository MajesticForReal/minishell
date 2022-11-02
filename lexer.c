/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:18:43 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/01 14:34:46 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_initialize_struct(void)
{
	t_lex	*curr;

	curr = malloc(sizeof(t_lex));
	if (!curr)
		return (NULL);
	curr->next = NULL;
	curr->token = -1;
	curr->str = NULL;
	return (curr);
}

int	ft_size_str(char *input, int i, char c)
{
	int	size;

	size = 0;
	if (input[i] == 34 || input[i] == 39)
	{
		size++;
		i++;
		return (size);
	}
	while (input[i] != '\0' && input[i] == c)
	{
		size++;
		i++;
	}
	return (size);
}

int	add_back(t_lex *start, int tok, char *input, int i, char c)
{
	t_lex	*new;
	int		j;
	int		size;

	new = ft_initialize_struct();
	while (start != NULL && start->next != NULL)
		start = start->next;
	start->next = new;
	new->token = tok;
	new->next = NULL;
	if (new->token == TOK_WORD)
	{
		i = ft_word(input, new, i);
		return (i);
	}
	j = 0;
	size = ft_size_str(input, i, c);
	new->str = malloc(sizeof(char) * (size + 1));
	size = size + i;
	while (i < size)
	{
		new->str[j] = input[i];
		i++;
		j++;
	}
	new->str[j] = '\0';
	return(i);
}

int	ft_size_str_word(char *input, int i)
{
	int	size;

	size = 0;
	while (input[i] != '|' && input[i] != 34 && input[i] != 36
		&& input[i] != 39 && input[i] != '<'
		&& input[i] != '>' && input[i] != ' '  && input[i] != '\t' && input[i] != '\0')
	{
		size++;
		i++;
	}
	return (size);
}

int	ft_word(char *input, t_lex *lex, int i)
{
	int		j;
	int		size;
	
	j = 0;
	size = ft_size_str_word(input, i);
	lex->str = malloc(sizeof(char) * (size + 1));
	while (j < size)
	{
		lex->str[j] = input[i];
		j++;
		i++;
	}
	lex->str[j] = '\0';
	lex->token = TOK_WORD;
	lex->next = NULL;
	return (i);
}

int	ft_first_lex(t_lex *lex, char *input)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
	{
		lex->token = TOK_SPACE;
		i++;
	}
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
	else if (input[i] != '|' && input[i] != 34 && input[i] != 36
		&& input[i] != 39 && input[i] != '<'
		&& input[i] != '>' && input[i] != ' ' && input[i] != '\t' && input[i] != '\0')
		{
			i = ft_word(input, lex, i);
			return (i);
		}
	size = ft_size_str(input, i, input[i]);
	lex->str = malloc(sizeof(char) * (size + 1));
	j = 0;
	while (j < size)
	{
		lex->str[j] = input[i];
		i++;
		j++;
	}
	lex->str[j] = '\0';
	lex->next = NULL;
	return (i);
}

void	ft_lexer(char *input, t_lex *lex)
{
	int		i;

	i = ft_first_lex(lex, input);
	while (input[i])
	{
		if (input[i] != '|' && input[i] != 34 && input[i] != 36
				&& input[i] != 39 && input[i] != '<'
				&& input[i] != '>' && input[i] != ' ' && input[i] != '\t')
				{
					i = add_back(lex, TOK_WORD, input, i, input[i]);
				}
		else if (input[i] == ' ' || input[i] == '\t')
			i = add_back(lex, TOK_SPACE, input, i, input[i]);
		else if (input[i] == '<')
			i = add_back(lex, TOK_IN, input, i, input[i]);
		else if (input[i] == '>')
			i = add_back(lex, TOK_OUT, input, i, input[i]);
		else if (input[i] == 34)
			i = add_back(lex, TOK_DQ, input, i, input[i]);
		else if (input[i] == 36)
			i = add_back(lex, TOK_DOLL, input, i, input[i]);
		else if (input[i] == 39)
			i = add_back(lex, TOK_SQ, input, i, input[i]);
		else if (input[i] == '|')
			i = add_back(lex, TOK_PIPE, input, i, input[i]);
	}
	i = 0;
}