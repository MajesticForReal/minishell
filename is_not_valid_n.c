/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_not_valid_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:19:54 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 18:11:05 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_not_valid_n1(t_exec *exec, t_utils *utils)
{
	if (utils->outfile != -1)
		ft_putstr_fd(" ", utils->outfile);
	else
		ft_putstr_fd(" ", exec->fd_cmd[1]);
}

void	ft_is_not_valid_n2(t_exec *exec, t_utils *utils)
{
	if (utils->outfile != -1)
		ft_putstr_fd("\n", utils->outfile);
	else
		ft_putstr_fd("\n", exec->fd_cmd[1]);
}

void	ft_is_not_valid_n4(t_lex *lex, t_exec *exec, t_utils *utils)
{
	if (utils->outfile != -1)
		ft_putstr_fd(lex->str, utils->outfile);
	else
		ft_putstr_fd(lex->str, exec->fd_cmd[1]);
}

void	ft_is_not_valid_n3(t_lex *lex, t_exec *exec, t_utils *utils)
{
	if (utils->outfile != -1)
	{
		ft_putstr_fd(lex->str, utils->outfile);
		ft_putstr_fd("\n", utils->outfile);
	}
	else
	{
		ft_putstr_fd(lex->str, exec->fd_cmd[1]);
		ft_putstr_fd("\n", exec->fd_cmd[1]);
	}
}

void	ft_is_not_valid_n(t_lex *lex, t_exec *exec, t_utils *utils)
{
	if (lex->token == TOK_SPACE && lex->next != NULL
		&& (lex->next->token == TOK_SPACE || lex->next->token == TOK_WORD))
		ft_is_not_valid_n1(exec, utils);
	else if (lex->token == TOK_SPACE && lex->next == NULL)
		ft_is_not_valid_n2(exec, utils);
	else if (lex->token == TOK_SPACE && lex->next->token != TOK_SPACE
		&& lex->next->token != TOK_WORD)
		ft_is_not_valid_n2(exec, utils);
	else if (lex->token == TOK_WORD && lex->next == NULL)
		ft_is_not_valid_n3(lex, exec, utils);
	else if (lex->token == TOK_WORD && lex->next != NULL)
		ft_is_not_valid_n4(lex, exec, utils);
	else if (lex->token == TOK_WORD && lex->next->token != TOK_WORD
		&& lex->next->token != TOK_SPACE)
		ft_is_not_valid_n4(lex, exec, utils);
	return ;
}
