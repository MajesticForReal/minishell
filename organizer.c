/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:31:10 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/02 19:43:43 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	ft_concat_quotes(t_lex **lex)
// {
// 	t_lex	*first;
// 	t_lex	*start;
// 	t_lex	*tmp;

// 	// first = malloc(sizeof(t_lex));
// 	// start = malloc(sizeof(t_lex));
// 	start = (*lex);
// 	first = (*lex);
// 	while ((*lex)->next != NULL)
// 	{
// 		while (start->next != NULL && start->token != TOK_DQ && start->token != TOK_SQ)
// 			start = start->next;
// 		if (start->next != NULL && start->next->next != NULL)
// 			(*lex) = start->next;
// 		if (start->token == TOK_DQ || start->token == TOK_SQ)
// 		{
// 			if ((*lex)->token == TOK_SPACE || (*lex)->token == TOK_IN || (*lex)->token == TOK_OUT || (*lex)->token == TOK_PIPE || (*lex)->token == TOK_FROMFROM || (*lex)->token == TOK_TOTO)
// 				(*lex)->token = 9;
// 			while ((*lex)->next != NULL && (*lex)->token != TOK_DQ
// 				&& (*lex)->next->token != TOK_DQ && (*lex)->token != TOK_SQ
// 				&& (*lex)->next->token != TOK_SQ)
// 			{
// 				printf("START : %s\n", start->str);
// 				printf("START NXT : %s\n", start->next->str);
// 				printf("LEX : %s\n", (*lex)->str);
// 				printf("LEX NXT : %s\n", (*lex)->next->str);
// 				tmp = ft_initialize_struct2((*lex)->str, (*lex)->next->str,
// 						(*lex)->next->next);
// 				start->next = tmp;
// 				free((*lex)->next);
// 				free((*lex));
// 				(*lex) = start;
// 				(*lex) = (*lex)->next;
// 			}
// 		}
// 		// if ((*lex)->token == TOK_SPACE || (*lex)->token == TOK_IN || (*lex)->token == TOK_OUT || (*lex)->token == TOK_PIPE || (*lex)->token == TOK_FROMFROM || (*lex)->token == TOK_TOTO)
// 		// 	(*lex)->token = 9;
// 		if (start->next != NULL)
// 			start = start->next;
// 		while (start->next != NULL && start->token != TOK_DQ && start->token != TOK_SQ)
// 			start = start->next;
// 		if (start->next != NULL)
// 			start = start->next;
// 		(*lex) = (*lex)->next;
// 	}
// 	if (first->token != TOK_DQ && first->token != TOK_SQ && (*lex)->next != NULL)
// 		first->next = start;
// 	(*lex) = first;
// }

void	ft_clear_quotes(t_lex **lex)
{
	t_lex	*first;
	t_lex	*lex_tmp;
	t_lex	*new;

	while (((*lex)->token == TOK_DQ || (*lex)->token == TOK_SQ) && (*lex)->next != NULL)
	{
		lex_tmp = (*lex);
		(*lex) = (*lex)->next;
		free(lex_tmp->str);
		free(lex_tmp);
	}
	first = (*lex);
	while ((*lex) != NULL && (*lex)->next != NULL)
	{
		if ((*lex)->next->token == TOK_DQ || (*lex)->next->token == TOK_SQ)
		{
			lex_tmp = (*lex)->next;
			(*lex)->next = (*lex)->next->next;
			free(lex_tmp->str);
			free(lex_tmp);
		}
		if ((*lex)->next != NULL && (*lex)->next->token != TOK_DQ && (*lex)->next->token != TOK_SQ)
			(*lex) = (*lex)->next;
	}
	if (((*lex)->token == TOK_DQ || (*lex)->token == TOK_SQ) && (*lex)->next == NULL)
	{
		new = ft_initialize_struct();
		lex_tmp = (*lex);
		(*lex) = new;
		free(lex_tmp->str);
		free(lex_tmp);
	}
	else
		(*lex) = first;
}



void	ft_concat_clear(t_lex **lex)
{
	t_lex	*first;
	t_lex	*lex_tmp;
	char	*newstr;
	t_lex	*start;

	first = (*lex);
	start = (*lex);
	while ((*lex) != NULL && (*lex)->next != NULL)
	{
		// if ((*lex) != NULL && (*lex)->next != NULL && (*lex)->next->token == TOK_SPACE)
		// {
		// 	lex_tmp = (*lex)->next;
		// 	(*lex)->next = (*lex)->next->next;
		// 	free(lex_tmp->str);
		// 	free(lex_tmp);
		// 	start = (*lex);
		// }
		if ((*lex) != NULL && (*lex)->next != NULL
				&& (*lex)->token == TOK_WORD && (*lex)->next->token == TOK_WORD)
		{
			while ((*lex) != NULL && (*lex) == first && (*lex)->next != NULL && (*lex)->next->token == TOK_WORD)
			{
				newstr = ft_concat2((*lex)->str, (*lex)->next->str);
				(*lex)->str = newstr;
				lex_tmp = (*lex)->next;
				if ((*lex)->next->next != NULL)
					(*lex)->next = (*lex)->next->next;
				else
					(*lex)->next = NULL;
				free(lex_tmp);
			}
			while ((*lex) != NULL && (*lex) != first && (*lex)->next != NULL && (*lex)->next->token == TOK_WORD)
			{
				lex_tmp = ft_initialize_struct2((*lex)->str, (*lex)->next->str,
						(*lex)->next->next);
				start->next = lex_tmp;
				free((*lex)->next);
				free((*lex));
				(*lex) = lex_tmp;
			}
		}
		// if ((*lex) != NULL && (*lex)->next != NULL && (*lex)->next->token == TOK_SPACE)
		// {
		// 	lex_tmp = (*lex)->next;
		// 	(*lex)->next = (*lex)->next->next;
		// 	free(lex_tmp->str);
		// 	free(lex_tmp);
		// 	start = (*lex);
		// }
		if ((*lex) != NULL && (*lex)->next != NULL)
		{
			(*lex) = (*lex)->next;
			if ((*lex)->token != TOK_WORD)
				start = (*lex);
		}
		else
			break;
	}
	(*lex) = first;
}

int	ft_check_quotes(t_lex *lex)
{
	t_lex *first;
	int	i;

	first = lex;
	while (lex != NULL)
	{
		if (lex != NULL && lex->next != NULL && lex->token == TOK_DQ)
		{
			lex = lex->next;
			while (lex != NULL && lex->next != NULL && lex->token != TOK_DQ)
			{
				if (lex->token != TOK_DOLL)
					lex->token = TOK_WORD;
				lex = lex->next;
			}
			if (lex->next != NULL)
				lex = lex->next;
		}
		else if (lex != NULL && lex->next != NULL && lex->token == TOK_SQ)
		{
			lex = lex->next;
			while (lex != NULL && lex->next != NULL && lex->token != TOK_SQ)
			{
				lex->token = TOK_WORD;
				lex = lex->next;
			}
			if (lex->next != NULL)
				lex = lex->next;
		}
		else
			lex = lex->next;
	}
	lex = first;
	i = 0;
	while (lex != NULL)
	{
		if (lex->token == TOK_DQ || lex->token == TOK_SQ)
		{
			if (i == 0)
			{
				i = ft_quotes(lex);
				if (i != 1)
				{
					return (-1);
				}
			}
			else
				return (0);
		}
		lex = lex->next;
	}
	return (0);
}

void	ft_organizer_heredoc(char *input, int fd)
{
	ft_dollar_heredoc(input, fd);
}

void	ft_organizer(t_lex **lex)
{
	ft_clear_quotes(lex);
	ft_concat_clear(lex);
}