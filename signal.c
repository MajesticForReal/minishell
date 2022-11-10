/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:44:44 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 15:59:19 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_detect_sig(int sig)
{
	if(sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("minishell > ", 2);
		g_exstat = 130;
	}
	else
	{
		ft_putstr_fd("minishell > ", 2);
		g_exstat = 127;
		return ;
	}
}