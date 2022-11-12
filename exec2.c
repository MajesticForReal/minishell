/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:04:32 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/12 22:05:28 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd_cmd(t_exec *exec)
{
	while (exec != NULL && exec->cmd[0] != NULL)
	{
		exec->fd_cmd[0] = dup(STDIN_FILENO);
		exec->fd_cmd[1] = dup(STDOUT_FILENO);
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return ;
}

void	ft_init_fd_cmd_no_pipe(t_exec *exec)
{
	while (exec != NULL && exec->cmd[0] != NULL)
	{
		exec->fd_cmd[0] = dup(STDIN_FILENO);
		exec->fd_cmd[1] = dup(STDOUT_FILENO);
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return ;
}

void	ft_constructor_cmd_2(t_exec *exec, char *new_path, char *my_cmd, int i)
{
	while (exec->path && exec->path[i])
	{
		free(new_path);
		new_path = NULL;
		new_path = ft_strcat_path(exec->path[i], my_cmd);
		if (new_path == NULL)
			return ;
		exec->cmd[0] = new_path;
		if (access(new_path, X_OK) == 0)
			execve(new_path, exec->cmd, NULL);
		i++;
	}
}

void	ft_constructor_cmd(t_exec *exec)
{
	int		i;
	char	*new_path;
	char	*my_cmd;
	char	*cmd_base;

	cmd_base = ft_strdup(exec->cmd[0]);
	new_path = NULL;
	my_cmd = ft_strdup(exec->cmd[0]);
	i = 0;
	if (ft_check_str(cmd_base, 2) == -1)
	{
		write(2, cmd_base, ft_strlen(cmd_base));
		write(2, ": No such file or directory\n", 28);
		free(my_cmd);
		free(cmd_base);
		return ;
	}
	ft_constructor_cmd_2(exec, new_path, my_cmd, i);
	write(2, cmd_base, ft_strlen(cmd_base));
	write(2, ": command not found\n", 20);
	free(new_path);
	free(my_cmd);
	free(cmd_base);
}

int	ft_check_str(char *str, int i)
{
	DIR	*d;

	if (i == 1)
	{
		d = opendir(str);
		if (d == NULL)
			return (0);
		closedir(d);
		return (-1);
	}
	else if (i == 2)
		if (ft_strchr(str, '/') != NULL)
			return (-1);
	return (0);
}
