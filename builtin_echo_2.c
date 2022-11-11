/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:50:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/11 16:08:30 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_echo_only(t_exec *exec)
{
	ft_putstr_fd("\n", exec->fd_cmd[1]);
	return (SUCCESS);
}

void	ft_print_argument(t_lex *lex, int valid_n, t_exec *exec)
{
	if (valid_n == 1)
		ft_is_valid_n(lex, exec);
	else
		ft_is_not_valid_n(lex, exec);
}

void	ft_builtin_echo_option(t_lex *lex, t_exec *exec)
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
			ft_print_argument(lex, valide_n, exec);
			lex = lex->next;
			print_n_now = 1;
		}
	}
}