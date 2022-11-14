/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:42:48 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/13 03:02:24 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_builtin_pwd(int option, t_exec *exec, t_utils *utils)
{
	char	*path_dir;

	path_dir = NULL;
	path_dir = getcwd(path_dir, 0);
	if (path_dir == NULL)
	{
		free(path_dir);
		return (NULL);
	}
	else if (path_dir != NULL && option == 1)
	{
		if (utils->outfile != -1)
		{
			ft_putstr_fd(path_dir, utils->outfile);
			ft_putstr_fd("\n", utils->outfile);
		}
		else
		{
			ft_putstr_fd(path_dir, exec->fd_cmd[1]);
			ft_putstr_fd("\n", exec->fd_cmd[1]);
		}
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
