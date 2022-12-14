/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:50:22 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 16:25:13 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_echo_only(t_exec *exec, t_utils *utils)
{
	if (utils->outfile != -1)
		ft_putstr_fd("\n", utils->outfile);
	else
		ft_putstr_fd("\n", exec->fd_cmd[1]);
	return (SUCCESS);
}

void	ft_print_argument(t_lex *lex, int valid_n, t_exec *exec, t_utils *utils)
{
	if (valid_n == 1)
		ft_is_valid_n(lex, exec, utils);
	else
		ft_is_not_valid_n(lex, exec, utils);
}

int	ft_builtin_echo_option_2(t_lex **lex, int *valide_n)
{
	if ((*lex)->next != NULL)
		(*lex) = (*lex)->next;
	if ((*lex)->next != NULL && (*lex)->next->token == TOK_WORD)
		(*lex) = (*lex)->next;
	else
		return (FAIL);
	*valide_n = 1;
	return (SUCCESS);
}

void	ft_builtin_echo_option(t_lex *lex, t_exec *exec, t_utils *utils)
{
	int	valide_n;
	int	print_n_now;

	print_n_now = 0;
	valide_n = 0;
	if (lex != NULL)
		lex = lex->next;
	while (lex != NULL)
	{
		if (lex->token != TOK_WORD && lex->token != TOK_SPACE)
			return ;
		else if (ft_builtin_echo_detect_n(lex->str) == 1 && print_n_now == 0)
		{
			if (ft_builtin_echo_option_2(&lex, &valide_n) == FAIL)
				return ;
		}
		else
		{
			ft_print_argument(lex, valide_n, exec, utils);
			lex = lex->next;
			print_n_now = 1;
		}
	}
}
