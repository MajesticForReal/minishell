/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:52:31 by klaurier          #+#    #+#             */
/*   Updated: 2022/06/23 13:21:29 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_exec_cmd_no_env(char **cmd, char **path, t_pipex *pipex)
{
	pipex->new_path = NULL;
	pipex->my_cmd = ft_strdup(cmd[0]);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, NULL);
		perror(cmd[0]);
		free(pipex->my_cmd);
		return ;
	}
	ft_exec_cmd_env(cmd, path, pipex);
	return ;
}

void	ft_exec_cmd_env(char **cmd, char **path, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		free(cmd[0]);
		cmd[0] = NULL;
		pipex->new_path = ft_strcat_cmd(path[i], pipex->my_cmd, '/');
		if (pipex->new_path == NULL)
			return ;
		cmd[0] = pipex->new_path;
		if (access(pipex->new_path, X_OK) == 0)
			execve(pipex->new_path, cmd, NULL);
		i++;
	}
	ft_execve_fail(pipex->my_cmd);
	return ;
}

void	ft_dup_and_close(t_pipex *pipex, int x)
{
	if (pipex->pipe_fd[0] != -1 && x == 1)
		close(pipex->pipe_fd[0]);
	if (pipex->fd_out != -1 && x == 1)
		close(pipex->fd_out);
	dup2(pipex->fd_in, 0);
	if (pipex->fd_in != -1 && x == 1)
		close(pipex->fd_in);
	dup2(pipex->pipe_fd[1], 1);
	if (pipex->pipe_fd[1] != -1 && x == 1)
		close(pipex->pipe_fd[1]);
	if (pipex->pipe_fd[1] != -1 && x == 2)
		close(pipex->pipe_fd[1]);
	if (pipex->fd_in != -1 && x == 2)
		close(pipex->fd_in);
	dup2(pipex->pipe_fd[0], 0);
	if (pipex->pipe_fd[0] != -1 && x == 2)
		close(pipex->pipe_fd[0]);
	dup2(pipex->fd_out, 1);
	if (pipex->fd_out != -1 && x == 2)
		close(pipex->fd_out);
}

void	ft_fork_child_2(t_pipex *pipex)
{
	if (pipex->status_fd_out != -1)
	{
		pipex->child_2 = fork();
		if (pipex->child_2 == -1)
		{
			perror("fork");
			ft_error(pipex, pipex->pipe_fd);
		}
		if (pipex->child_2 == 0)
		{
			ft_dup_and_close(pipex, 2);
			ft_exec_cmd_no_env(pipex->cmd2, pipex->path, pipex);
			if (pipex->fd_in != -1)
				close(pipex->fd_in);
			ft_free_all(pipex);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_fork_child(t_pipex *pipex)
{
	if (pipex->status_fd_in != -1)
	{
		pipex->child = fork();
		if (pipex->child == -1)
		{
			perror("fork");
			ft_error(pipex, pipex->pipe_fd);
		}
		if (pipex->child == 0)
		{
			ft_dup_and_close(pipex, 1);
			ft_exec_cmd_no_env(pipex->cmd1, pipex->path, pipex);
			if (pipex->fd_out != -1)
				close(pipex->fd_out);
			ft_free_all(pipex);
			exit(EXIT_FAILURE);
		}
	}
}
