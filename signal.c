/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:44:44 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 21:57:16 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_detect_sig_child(int sig)
{
	if (sig == SIGINT && g_exstat == 42)
	{
		sig = SIGQUIT;
		g_exstat = 2;
		write(2, "\n", 1);
	}
	else if (sig == SIGINT && g_exstat != 42)
	{
		sig = SIGQUIT;
		g_exstat = 2;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT && g_exstat == 42)
	{
		g_exstat = 3;
	}
	else if (sig == SIGQUIT && g_exstat != 42)
	{
		g_exstat = 3;
		write(2, "Quit (core dumped)\n",
			ft_strlen("Quit (core dumped)\n"));
	}
}

void	ft_detect_sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_exstat = 130;
		sig = SIGCONT;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_detect_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exstat = 2;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
