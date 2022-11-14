/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_w_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:41:27 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/14 18:08:38 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtin_pipe(t_exec *exec, t_utils *utils, t_lex *lex,
		t_env *env, t_env *export)
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
	// ft_pipe_redir(exec, utils);
	dprintf(2, "AV INFILE : %d\n", utils->infile);
	dprintf(2, "AV OUTFILE : %d\n", utils->outfile);
	dprintf(2, "AV CMD 0 : %d\n", exec->fd_cmd[0]);
	dprintf(2, "AV CMD 1 : %d\n", exec->fd_cmd[1]);
	dprintf(2, "AV PIPE 0 : %d\n", utils->fd_pipe[0]);
	dprintf(2, "AV PIPE 1 : %d\n", utils->fd_pipe[1]);
	ft_all_builtin(lex, env, utils, exec, export);
	ft_close_files(utils->infile, utils->outfile);
	if (exec->next == NULL)
	{
		if (utils->fd_pipe[0] != STDIN_FILENO)
			close(exec->fd_cmd[0]);
		if (utils->fd_pipe[1] != STDOUT_FILENO)
			close(utils->fd_pipe[1]);
	}
	return ;
}

void	ft_exec_pipe(t_exec *exec, t_utils *utils, t_env *env, t_lex *lex,
		t_env *export)
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
			ft_processus_pipe(exec, env, lex, utils, export);
		}
		else if (ft_check_builtin(exec) == 1 && exec->process_id == 0)
		{
			dprintf(2, "COUCOU\n");
			if (exec != NULL && exec->next != NULL)
				close(exec->next->fd_cmd[0]);
			ft_exec_builtin_pipe(exec, utils, lex, env, export);
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

void	ft_processus_pipe(t_exec *exec, t_env *env, t_lex *lex, t_utils *utils,
		t_env *export)
{
	if (exec != NULL && exec->next != NULL)
		close(exec->next->fd_cmd[0]);
	ft_connect_fd_cmd(exec);
	ft_connect_redir(exec, utils);
	if (exec->cmd != NULL && exec->cmd[0][0] == '.' && exec->cmd[0][1] == '/')
		ft_exec_prog(exec);
	else
	{
		if (env->str == NULL)
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
		if (env->str != NULL)
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
	// ft_pipe_redir(exec, utils);
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
