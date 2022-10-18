/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:09:54 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/17 16:03:45 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//permet de faire la commande "echo" sans argument ni option
int	ft_builtin_echo_only(char *input)
{
	printf("\n");
	(void)input;
	return (SUCCESS);
}
// permet de faire la commande "echo salut" par exemple
int	ft_builtin_echo(char *input)
{
	char	**strs;

	strs = ft_split(input, ' ');
	printf("%s\n",strs[1]);
	free(strs);
	return (1);

}
//permet de faire la commande "echo -n", "echo -n salut", "echo -nnn -nnn salut", "echo -nnn -nan salut -n"
int	ft_builtin_echo_option_2(char *input)
{
	char	**strs;
	int	i;
	int	j;
	int	start_to_print;

	start_to_print = 0;
	i = 1;
	j = 1;
	strs = ft_split(input, ' ');
	while(strs[i] != NULL)
	{
		while(strs[i][j] != '\0')
		{
			if(strs[1][0] != '-' && strs[1][1] != 'n')
				ft_print_2_d_tab(strs, 1);
			if(strs[i][j] != 'n')
			{
				ft_print_2_d_tab(strs, i);
				return (1);
			}
			j++;
		}
		j = 1;
		i++;
	}
	(void)start_to_print;
	free(strs);
	return (1);
}