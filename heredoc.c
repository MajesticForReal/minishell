/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:03:00 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 23:27:51 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	ft_heredoc0(&tmp);
	if (tmp->token == TOK_TOTO)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		if(tmp->next != NULL && tmp->next->token == TOK_WORD)
		{
			limiter = tmp->next->str;
			input = limiter + 1;
		}
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0744);
		ft_heredoc2(input, limiter, fd);
	}
	else
		return ;
}

void	ft_heredoc0(t_lex **tmp)
{
	while ((*tmp)->token != TOK_TOTO && (*tmp) != NULL && (*tmp)->next != NULL)
	{
		if((*tmp)->token == TOK_PIPE)
			return ;
		(*tmp) = (*tmp)->next;
	}

	
}

int	ft_heredoc2(char *input, char *limiter, int fd)
{
		while (1)
		{
			input = readline(" >>");
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