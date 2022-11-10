/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:50:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 17:51:40 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_echo_only(void)
{
	ft_putstr_fd("\n", 1);
	return (SUCCESS);
}

void	ft_print_argument(t_lex *lex, int valid_n)
{
	if (valid_n == 1)
		ft_is_valid_n(lex);
	else
		ft_is_not_valid_n(lex);
}

void	ft_builtin_echo_option(t_lex *lex)
{
	int	valide_n;
	int	print_n_now;

	print_n_now = 0;
	valide_n = 0;
	lex = lex->next;
	while (lex != NULL)
	{
		if(lex->token != TOK_WORD && lex->token != TOK_SPACE)
			return;
		else if (ft_builtin_echo_detect_n(lex->str) == 1 && print_n_now == 0)
		{
			lex = lex->next;
			lex = lex->next;
			valide_n = 1;
		}
		else
		{
			ft_print_argument(lex, valide_n);
			lex = lex->next;
			print_n_now = 1;
		}
	}
}
