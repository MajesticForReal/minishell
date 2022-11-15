/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_no_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:03:00 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 17:22:10 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_no_cmd_1(t_lex **tmp, char *limiter, char *input)
{
	if ((*tmp)->next != NULL && (*tmp)->next->token != TOK_WORD)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->next != NULL && (*tmp)->next->token == TOK_WORD)
	{
		limiter = (*tmp)->next->str;
		input = limiter + 1;
	}
	(void)input;
}

int	ft_heredoc_no_cmd_next(t_lex **tmp)
{
	if ((*tmp)->next != NULL)
		(*tmp) = (*tmp)->next;
	else
		return (FAIL);
	return (SUCCESS);
}

void	ft_heredoc_no_cmd(t_lex *lex)
{
	t_lex	*tmp;
	int		fd;
	char	*limiter;
	char	*input;
	char	*file;

	file = ".HEREDOC";
	tmp = lex;
	limiter = NULL;
	input = NULL;
	while (tmp != NULL && tmp->token != TOK_PIPE)
	{
		ft_heredoc_no_cmd_0(&tmp);
		if (tmp->token == TOK_IN)
		{
			ft_heredoc_no_cmd_1(&tmp, limiter, input);
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0744);
			ft_heredoc2(input, limiter, fd);
		}
		else
			return ;
		if (ft_heredoc_no_cmd_next(&tmp) == FAIL)
			break ;
	}
	close(fd);
}

void	ft_heredoc_no_cmd_0(t_lex **tmp)
{
	while ((*tmp) != NULL && (*tmp)->token != TOK_IN && (*tmp)->next != NULL)
	{
		if ((*tmp)->token == TOK_PIPE)
			return ;
		(*tmp) = (*tmp)->next;
	}
}
