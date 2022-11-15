/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:44:44 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 18:41:52 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_detect_sig(int sig)
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
