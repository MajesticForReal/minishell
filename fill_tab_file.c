/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:51:08 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 00:07:50 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_tab_file3(t_lex **lex, t_exec *exec, int *i)
{
	if ((*lex)->token != TOK_WORD && (*lex)->token != TOK_SPACE
		&& (*lex)->token != TOK_PIPE)
	{
		exec->file[*i] = (*lex)->str;
		*i = *i + 1;
		if ((*lex)->next != NULL && (*lex)->next->token != TOK_PIPE)
			(*lex) = (*lex)->next;
		if ((*lex)->next != NULL && (*lex)->token == TOK_SPACE)
			(*lex) = (*lex)->next;
		if ((*lex)->token == TOK_WORD)
		{
			exec->file[*i] = (*lex)->str;
			*i = *i + 1;
		}
	}
}

void	ft_fill_tab_file2(t_lex **lex, t_exec *exec, int *i)
{
	if ((*lex)->token == TOK_TOTO)
	{
		exec->file[*i] = (*lex)->str + 1;
		*i = *i + 1;
		if ((*lex)->next != NULL)
			(*lex) = (*lex)->next;
		if ((*lex)->next != NULL && (*lex)->token == TOK_SPACE)
			(*lex) = (*lex)->next;
		if ((*lex)->token == TOK_WORD)
		{
			exec->file[*i] = exec->heredoc;
			*i = *i + 1;
			if ((*lex)->next != NULL)
				(*lex) = (*lex)->next;
		}
	}
}

void	ft_fill_tab_file(t_lex *lex, t_exec *exec)
{
	int	i;

	i = 0;
	while (lex != NULL && lex->token != TOK_PIPE)
	{
		ft_fill_tab_file2(&lex, exec, &i);
		ft_fill_tab_file3(&lex, exec, &i);
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
}

void	ft_malloc_tab_file_heredoc(t_lex **lex, t_exec *exec)
{
	if ((*lex)->token == TOK_TOTO)
	{
		exec->nb_file_redir++;
		if ((*lex)->next != NULL)
			(*lex) = (*lex)->next;
		if ((*lex)->next != NULL && (*lex)->token == TOK_SPACE)
			(*lex) = (*lex)->next;
		if ((*lex)->token == TOK_WORD)
			exec->nb_file_redir++;
	}
}

void	ft_malloc_tab_file(t_lex *lex, t_exec *exec)
{
	exec->nb_file_redir = 0;
	while (lex != NULL && lex->token != TOK_PIPE)
	{
		if (lex->token != TOK_WORD && lex->token != TOK_SPACE
			&& lex->token != TOK_PIPE)
		{
			exec->nb_file_redir++;
			if (lex->next != NULL && lex->next->token != TOK_PIPE)
				lex = lex->next;
			if (lex->next != NULL && lex->token == TOK_SPACE)
				lex = lex->next;
			if (lex->token == TOK_WORD)
				exec->nb_file_redir++;
		}
		ft_malloc_tab_file_heredoc(&lex, exec);
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	exec->file = malloc(sizeof(char *) * (exec->nb_file_redir + 1));
	if (exec->file == NULL)
		return ;
	exec->file[exec->nb_file_redir] = NULL;
}
