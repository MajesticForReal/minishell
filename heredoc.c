/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:03:00 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 23:18:56 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_lex *lex)
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
		ft_heredoc0(&tmp);
		if (tmp->token == TOK_TOTO)
		{
			if (tmp->next != NULL && tmp->next->token != TOK_WORD)
				tmp = tmp->next;
			if (tmp->next != NULL && tmp->next->token == TOK_WORD)
			{
				limiter = tmp->next->str;
				input = limiter + 1;
			}
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0744);
			ft_heredoc2(input, limiter, fd);
		}
		else
			return ;
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break ;
	}
}

void	ft_heredoc0(t_lex **tmp)
{
	while ((*tmp)->token != TOK_TOTO && (*tmp) != NULL && (*tmp)->next != NULL)
	{
		if ((*tmp)->token == TOK_PIPE)
			return ;
		(*tmp) = (*tmp)->next;
	}
}

int	ft_heredoc2(char *input, char *limiter, int fd)
{
	while (1)
	{
		input = readline(" >>");
		if (!input)
		{
			ft_putstr_fd("exit", 2);
			ft_putstr_fd("\n", 2);
			g_exstat = 0;
			return (1);
		}
		if (ft_strlen(input) == 0 && limiter != NULL)
			ft_organizer_heredoc(input, fd);
		else if (ft_strlen(input) != 0 && limiter == NULL)
			ft_organizer_heredoc(input, fd);
		else if (ft_strlen(input) == 0 && limiter == NULL)
			break ;
		else if (ft_compare(input, limiter) != SUCCESS)
			ft_organizer_heredoc(input, fd);
		else
			break ;
	}
	return (1);
}

void	ft_malloc_heredoc_str(t_exec *exec)
{
	int		i;
	char	*str;

	str = ".HEREDOC";
	i = 0;
	i = ft_strlen(".HERDOC");
	exec->heredoc = malloc(sizeof(char *) * i + 1);
	if (exec->heredoc == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		exec->heredoc[i] = str[i];
		i++;
	}
	exec->heredoc[i] = '\0';
}
