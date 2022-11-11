/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:42:48 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/11 16:00:32 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_builtin_pwd(int option, t_exec *exec)
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
		ft_putstr_fd(path_dir, exec->fd_cmd[1]);
		ft_putstr_fd("\n", exec->fd_cmd[1]);
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
