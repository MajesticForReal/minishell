/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:52:31 by klaurier          #+#    #+#             */
/*   Updated: 2022/06/22 18:07:11 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		ft_error(pipex, pipex->pipe_fd);
	}
	ft_fork_child(pipex);
	ft_fork_child_2(pipex);
	pipex->child = 0;
	pipex->child_2 = 0;
	close_fd(pipex);
	waitpid(pipex->child, &pipex->status, 0);
	waitpid(pipex->child_2, &pipex->status, 0);
}

void	ft_choose_cmd(char **argv, t_pipex *pipex)
{
	int	i;
	int	j;
	int	k;

	i = ft_detect_exeptional_case_1(argv);
	j = ft_detect_exeptional_case_2(argv);
	k = ft_detect_exeptional_case_3(i, j);
	if (k == 0 && argv[2][0] != '\0' && argv[3][0] != '\0')
		ft_get_cmd(argv, pipex);
	else if (k == 2 && argv[2][0] != '\0')
	{
		pipex->cmd2 = ft_split(argv[3], 'a');
		pipex->cmd1 = ft_split(argv[2], ' ');
	}
	else if (k == 1 && argv[3][0] != '\0')
	{
		pipex->cmd1 = ft_split(argv[2], 'a');
		pipex->cmd2 = ft_split(argv[3], ' ');
	}
	else if (k == 3)
	{
		pipex->cmd1 = ft_split(argv[2], 'a');
		pipex->cmd2 = ft_split(argv[3], 'a');
	}
}

void	ft_get_fd_in(char **argv, t_pipex *pipex)
{
	pipex->status_fd_in = 1;
	pipex->status_fd_out = 1;
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in < 0)
	{
		perror(argv[1]);
		pipex->status_fd_in = -1;
	}
	pipex->fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_out < 0)
	{
		perror(argv[4]);
		if (pipex->fd_in != -1)
			close(pipex->fd_in);
		ft_free_all(pipex);
		exit(EXIT_FAILURE);
		pipex->status_fd_out = -1;
	}
}

int	main_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		return (-1);
	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (-1);
	if (ft_detect_exeptional_case_0(argv, pipex) == 1)
	{
		ft_exeptional_case_1(pipex, argv);
		return (0);
	}
	ft_get_path_cmd(argv, envp, pipex);
	ft_choose_cmd(argv, pipex);
	ft_get_fd_in(argv, pipex);
	ft_pipex(pipex);
	ft_free_all(pipex);
	return (0);
}
