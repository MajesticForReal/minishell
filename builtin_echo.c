/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:09:54 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/02 17:03:34 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//permet de faire la commande "echo" sans argument ni option
int	ft_builtin_echo_only(void)
{
	ft_putstr_fd("\n", 1);
	return (SUCCESS);
}
//permet de faire la commande "echo -n", "echo -n salut", "echo -nnn -nnn salut", "echo -nnn -nan salut -n"
void	ft_not_n(t_lex *lex, int *valide_n)
{
	if(lex->next == NULL)
	{
		if(*valide_n == 1)
		{
			ft_putstr_fd(lex->str, 1);
			return ;
		}	
		else
		{
			ft_putstr_fd(lex->str, 1);
			ft_putstr_fd("\n", 1);
			return ;
		}
	}
	else
	{
		ft_putstr_fd(lex->str, 1);
		// ft_putchar_fd(' ', 1);
	}
}

void	ft_builtin_echo_option(t_lex *lex)
{
	int	valide_n;
	int	print_n_now;

	print_n_now = 0;
	valide_n = 0;
	lex = lex->next;
	while(lex != NULL)
	{
		if(ft_builtin_echo_detect_n(lex->str) == 1 && print_n_now == 0) 
			{
				lex = lex->next;
				valide_n = 1;
			}
		else
		{
			ft_not_n(lex, &valide_n);
			lex = lex->next;
			print_n_now = 1;
		}
	}
}

int	ft_builtin_echo_detect_n(char *lex_str)
{
	int	i;

	i = 0;
	if(lex_str[0] == '-' && lex_str[1] == 'n')
		i = 2;
	else
		return (0);
	while(lex_str[i] != '\0')
	{
		if(lex_str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_builtin_echo_all(t_lex *lex,t_env *env)
{
	// if(lex->next->token != TOK_SPACE)
		// return ;
	if(lex->next == NULL)
		ft_builtin_echo_only();
	else if(lex->next != NULL)
		ft_builtin_echo_option(lex);
		
	(void)env;
	(void)lex;
}
