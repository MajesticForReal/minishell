/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:56:40 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 15:25:05 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_option_execve(t_lex *lex, t_exec *exec)
{
	exec->nb_option = 0;
	while (lex != NULL && lex->token != TOK_PIPE)
	{
		if (lex->token == TOK_WORD)
			exec->nb_option++;
		if (lex->token != TOK_WORD && lex->token != TOK_SPACE)
		{
			if (lex->next != NULL)
				lex = lex->next;
			if (lex->next != NULL && lex->token == TOK_SPACE)
				lex = lex->next;
		}
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	exec->cmd = malloc(sizeof(char *) * (exec->nb_option + 1));
	if (exec->cmd == NULL)
		return ;
	exec->cmd[exec->nb_option] = NULL;
}

void	ft_fill_tab_cmd(t_lex *lex, t_exec *exec)
{
	int	i;

	i = 0;
	while (lex != NULL && lex->token != TOK_PIPE)
	{
		if (lex->token == TOK_WORD)
		{
			exec->cmd[i] = lex->str;
			i++;
		}
		if (lex->token != TOK_WORD && lex->token != TOK_SPACE)
		{
			if (lex->next != NULL)
				lex = lex->next;
			if (lex->next != NULL && lex->token == TOK_SPACE)
				lex = lex->next;
		}
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
}

int	ft_organizer_exec(t_lex *lex, t_exec *exec, t_utils *utils)
{
	while (lex != NULL)
	{
		ft_malloc_heredoc_str(exec);
		ft_heredoc(lex);
		if (utils->ambigous == 1)
		{
			while (lex != NULL && lex->str[0] != '$')
			{
				if (lex->next != NULL)
					lex = lex->next;
				else
					break ;
			}
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(lex->str, 2);
			ft_putstr_fd(lex->next->str, 2);
			ft_putstr_fd(": ambigous redirect\n", 2);
			return (FAIL);
		}
		if (exec != NULL && exec->path == NULL)
		{
			exec->path = ft_split(ft_find_path(utils->env), ':');
		}
		ft_malloc_option_execve(lex, exec);
		ft_fill_tab_cmd(lex, exec);
		ft_malloc_tab_file(lex, exec);
		ft_fill_tab_file(lex, exec);
		while (lex != NULL && lex->token != TOK_PIPE)
		{
			if (lex->next != NULL)
				lex = lex->next;
			else
				return (SUCCESS);
		}
		if (lex != NULL && lex->token == TOK_PIPE)
		{
			ft_next_exec(exec);
			if (exec->next != NULL)
				exec = exec->next;
			if (lex->next != NULL)
				lex = lex->next;
		}
	}
	return (SUCCESS);
}