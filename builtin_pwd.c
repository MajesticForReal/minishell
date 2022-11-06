/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:42:48 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/06 20:27:49 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//permet de faire la commande pwd sans argument ni option
char	*ft_builtin_pwd(int option)
{
	char	*path_dir;

	path_dir = NULL;
	path_dir = getcwd(path_dir, 2000);
	if (path_dir == NULL)
	{
		free(path_dir);
		return (NULL);
	}
	else if (path_dir != NULL && option == 1)
	{
		ft_putstr_fd(path_dir, 1);
		ft_putstr_fd("\n", 1);
		free(path_dir);
		return (NULL);
	}
	else if (path_dir != NULL && option == 2)
	{
		return (path_dir);
	}
	free(path_dir);
	return (NULL);
}
