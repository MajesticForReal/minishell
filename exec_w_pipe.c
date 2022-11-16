/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_w_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:41:27 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/16 19:12:38 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_processus_pipe_cmd(t_lex *lex, t_exec *exec, t_utils *utils)
{
	if (utils->env->str == NULL)
	{
		if (access(exec->cmd[0], X_OK) == 0)
			execve(exec->cmd[0], exec->cmd, NULL);
		else
		{
			g_exstat = 127;
			write(2, "minishell: ", 12);
			write(2, exec->cmd[0], ft_strlen(exec->cmd[0]));
			write(2, ": command not found\n", 20);
			ft_exit(lex, utils->env, utils, exec);
		}
	}
	if (utils->env->str != NULL)
	{
		if (access(exec->cmd[0], X_OK) == 0)
			execve(exec->cmd[0], exec->cmd, NULL);
		else
			ft_constructor_cmd(exec);
		if (utils->infile != -1)
			close(utils->infile);
		if (utils->outfile != -1)
			close(utils->outfile);
		ft_exit(lex, utils->env, utils, exec);
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

void	ft_connect_redir(t_utils *utils)
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
