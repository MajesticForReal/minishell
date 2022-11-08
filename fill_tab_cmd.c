/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:56:40 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/08 22:26:50 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_option_execve(t_lex *lex, t_exec *exec)
{
	while(lex != NULL && lex->token != TOK_PIPE)
	{
		if(lex->token == TOK_WORD)
			exec->nb_option++;
		if(lex->token != TOK_WORD && lex->token != TOK_SPACE)
		{
			if(lex->next != NULL)
				lex = lex->next;
			if(lex->next != NULL && lex->token == TOK_SPACE)
				lex = lex->next;
		}
		if(lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	exec->cmd = malloc(sizeof(char *) * exec->nb_option + 1);
	if(exec->cmd == NULL)
		return ;
	exec->cmd[exec->nb_option] = NULL;
}

void	ft_fill_tab_cmd(t_lex *lex, t_exec *exec)
{
	int	i;

	i = 0;
	while(lex != NULL && lex->token != TOK_PIPE)
	{
		if(lex->token == TOK_WORD)
		{
			exec->cmd[i] = lex->str;
			i++;
		}
		if(lex->token != TOK_WORD && lex->token != TOK_SPACE)
		{
			if(lex->next != NULL)
				lex = lex->next;
			if(lex->next != NULL && lex->token == TOK_SPACE)
				lex = lex->next;
		}
		if(lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
}

void ft_organizer_exec(t_lex *lex, t_exec *exec, t_env *env)
{
	while(lex != NULL)
	{
		ft_malloc_heredoc_str(exec);
		ft_heredoc(lex);
		exec->path = ft_split(ft_find_path(env), ':');
		ft_malloc_option_execve(lex, exec);
		ft_fill_tab_cmd(lex, exec);
		ft_malloc_tab_file(lex, exec);
		ft_fill_tab_file(lex, exec);
		while(lex != NULL && lex->token != TOK_PIPE)
		{
			if(lex->next != NULL)
				lex = lex->next;
			else
				return ;
		}
		if(lex->token == TOK_PIPE)
		{
			ft_next_exec(exec);
			exec = exec->next;
			lex = lex->next;
		}
	}
}