/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:09:54 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 17:51:37 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_valid_n(t_lex *lex)
{
		if(lex->token == TOK_SPACE && lex->next != NULL
		&& (lex->next->token == TOK_SPACE
		|| lex->next->token == TOK_WORD))
		{
			ft_putstr_fd(" ", 1);
			return ;
		}
		else if(lex->token == TOK_SPACE && lex->next == NULL)
			return ;
		else if(lex->token == TOK_SPACE && lex->next->token != TOK_SPACE && lex->next->token != TOK_WORD)
			return ;
		else if(lex->token == TOK_WORD)
			ft_putstr_fd(lex->str, 1);
		return ;
}


void	ft_is_not_valid_n(t_lex *lex)
{
		if(lex->token == TOK_SPACE && lex->next != NULL
			&& (lex->next->token == TOK_SPACE
			|| lex->next->token == TOK_WORD))
			ft_putstr_fd(" ", 1);
		else if(lex->token == TOK_SPACE && lex->next == NULL)
			ft_putstr_fd("\n", 1);
		else if(lex->token == TOK_SPACE && lex->next->token != TOK_SPACE && lex->next->token != TOK_WORD)
			ft_putstr_fd("\n", 1);
		else if(lex->token == TOK_WORD && lex->next == NULL)
		{
			ft_putstr_fd(lex->str, 1);
			ft_putstr_fd("\n", 1);
		}
		else if(lex->token == TOK_WORD && lex->next != NULL)
			ft_putstr_fd(lex->str, 1);
		else if(lex->token == TOK_WORD && lex->next->token != TOK_WORD && lex->next->token != TOK_SPACE)
			ft_putstr_fd(lex->str, 1);
		return ;
}

int	ft_builtin_echo_detect_n(char *lex_str)
{
	int	i;

	i = 0;
	
	if (lex_str[0] == '-' && lex_str[1] == 'n')
		i = 2;
	else
		return (0);
	while (lex_str[i] != '\0')
	{
		if (lex_str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_builtin_echo_all(t_lex *lex, t_env *env)
{
	if(lex->next != NULL && lex->next->token == TOK_SPACE)
	{
		lex = lex->next;
		if(lex->next != NULL && lex->next->token == TOK_WORD)
		{
			ft_builtin_echo_option(lex);
		}
		else
			ft_builtin_echo_only();
	}
	else
		ft_builtin_echo_only();
		
	(void)env;
	(void)lex;
}
