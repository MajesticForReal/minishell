/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_w_pipe2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:04:46 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/15 23:59:39 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtin_pipe(t_exec *exec, t_utils *utils, t_lex *lex)
{
	ft_all_builtin(lex, utils, exec);
	ft_close_files(utils->infile, utils->outfile);
	if (exec->fd_cmd[0] != STDIN_FILENO)
		close(exec->fd_cmd[0]);
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
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
		}
		ft_exec_pipe_fork(exec, utils, lex);
		exec = exec->next;
	}
}

void	ft_exec_pipe_fork(t_exec *exec, t_utils *utils, t_lex *lex)
{
	exec->process_id = fork();
	if (exec->process_id < 0)
		return (perror("minishell: fork: "));
	signal(SIGINT, ft_detect_sig_child);
	signal(SIGQUIT, ft_detect_sig_child);
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
		ft_exit(lex, utils->env, utils, exec);
	}
	if (exec->fd_cmd[0] != STDIN_FILENO)
		close(exec->fd_cmd[0]);
	if (exec->fd_cmd[1] != STDOUT_FILENO)
		close(exec->fd_cmd[1]);
	ft_close_files(utils->infile, utils->outfile);
}

void	ft_processus_pipe(t_exec *exec, t_lex *lex, t_utils *utils)
{
	if (exec != NULL && exec->next != NULL)
		close(exec->next->fd_cmd[0]);
	ft_connect_fd_cmd(exec);
	ft_connect_redir(utils);
	if (exec->cmd != NULL && exec->cmd[0][0] == '.' && exec->cmd[0][1] == '/')
		ft_exec_prog(exec);
	else
		ft_processus_pipe_cmd(lex, exec, utils);
}
