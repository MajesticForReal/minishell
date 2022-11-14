/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_w_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:41:27 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/14 23:06:57 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtin_pipe(t_exec *exec, t_utils *utils, t_lex *lex)
{
	ft_all_builtin(lex, utils, exec);
	ft_close_files(utils->infile, utils->outfile);
	if (utils->fd_pipe[0] != STDIN_FILENO)
		close(utils->fd_pipe[0]);
	if (utils->fd_pipe[1] != STDOUT_FILENO)
		close(utils->fd_pipe[1]);
}

void	ft_exec_pipe(t_exec *exec, t_utils *utils, t_lex *lex)
{
	ft_init_fd_cmd(exec);
	while (exec != NULL)
	{
		ft_pipe_redir(exec, utils);
		if (exec->next != NULL && exec->cmd[0] != NULL)
		{
			if (pipe(utils->fd_pipe) == -1)
				return (perror("minishell: pipe: "));
			exec->next->fd_cmd[0] = utils->fd_pipe[0];
			exec->fd_cmd[1] = utils->fd_pipe[1];
		}
		exec->process_id = fork();
		if (exec->process_id < 0)
			return (perror("minishell: fork: "));
		signal(SIGINT, ft_detect_sig);
		signal(SIGQUIT, ft_detect_sig);
		if (ft_check_builtin(exec) != 1 && exec->process_id == 0)
		{
			ft_processus_pipe(exec, lex, utils);
		}
		else if (ft_check_builtin(exec) == 1 && exec->process_id == 0)
		{
			if (exec != NULL && exec->next != NULL)
				close(exec->next->fd_cmd[0]);
			ft_exec_builtin_pipe(exec, utils, lex);
			g_exstat = 2;
			exit(EXIT_FAILURE);
		}
		if (exec->fd_cmd[0] != STDIN_FILENO)
			close(exec->fd_cmd[0]);
		if (exec->fd_cmd[1] != STDOUT_FILENO)
			close(exec->fd_cmd[1]);
		ft_close_files(utils->infile, utils->outfile);
		exec = exec->next;
	}
}

void	ft_processus_pipe(t_exec *exec, t_lex *lex, t_utils *utils)
{
	if (exec != NULL && exec->next != NULL)
		close(exec->next->fd_cmd[0]);
	ft_connect_fd_cmd(exec);
	ft_connect_redir(exec, utils);
	if (exec->cmd != NULL && exec->cmd[0][0] == '.' && exec->cmd[0][1] == '/')
		ft_exec_prog(exec);
	else
	{
		if (utils->env->str == NULL)
		{
			if (access(exec->cmd[0], X_OK) == 0)
				execve(exec->cmd[0], exec->cmd, NULL);
			else
			{
				write(2, exec->cmd[0], ft_strlen(exec->cmd[0]));
				write(2, ": command not found\n", 20);
				return ;
			}
		}
		if (utils->env->str != NULL)
		{
			if (access(exec->cmd[0], X_OK) == 0)
				execve(exec->cmd[0], exec->cmd, NULL);
			else
			{
				ft_constructor_cmd(exec);
			}
		}
		if (utils->infile != -1)
			close(utils->infile);
		if (utils->outfile != -1)
			close(utils->outfile);
		exit(EXIT_FAILURE);
	}
}

void	ft_connect_fd_cmd(t_exec *exec)
{
	if (exec->fd_cmd[0] != STDIN_FILENO)
	{
		dup2(exec->fd_cmd[0], STDIN_FILENO);
		close(exec->fd_cmd[0]);
	}
	if (exec->fd_cmd[1] != STDOUT_FILENO)
	{
		dup2(exec->fd_cmd[1], STDOUT_FILENO);
		close(exec->fd_cmd[1]);
	}
}

int	ft_pipe_redir(t_exec *exec, t_utils *utils)
{
	if (ft_open_out(exec, utils) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_open_in(exec, utils) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_open_toto(exec, utils) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_connect_redir(t_exec *exec, t_utils *utils)
{
	if (utils->infile != -1)
	{
		dup2(utils->infile, STDIN_FILENO);
		close(utils->infile);
	}
	if (utils->outfile != -1)
	{
		dup2(utils->outfile, STDOUT_FILENO);
		close(utils->outfile);
	}
}
