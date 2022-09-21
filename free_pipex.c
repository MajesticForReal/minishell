/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:03:08 by klaurier          #+#    #+#             */
/*   Updated: 2022/06/23 12:28:45 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2dchar(char **tab)
{
	size_t	i;

	i = 0;
	while (tab != NULL && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	close_fd(t_pipex *pipex)
{
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
}

void	ft_free_all(t_pipex *pipex)
{
	ft_free_2dchar(pipex->path);
	ft_free_2dchar(pipex->cmd2);
	ft_free_2dchar(pipex->cmd1);
	free(pipex);
}

void	ft_error(t_pipex *pipex, int *pipe_fd)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	ft_free_all(pipex);
	exit(EXIT_FAILURE);
}

void	ft_execve_fail(char *my_cmd)
{
	ft_putstr(my_cmd);
	write(2, ": command not found\n", 21);
	free(my_cmd);
}
