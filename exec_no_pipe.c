/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:18:23 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/12 23:19:52 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_no_pipe_redir(t_exec *exec, t_utils *utils)
{
	while (exec != NULL && exec->file != NULL)
	{
		if (ft_open_out(exec, utils) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_open_in(exec, utils) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_open_toto(exec, utils) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

void	ft_processus_no_pipe(t_exec *exec, t_env *env, t_utils *utils, t_env *export)
{
	dup_n_close(utils->infile, STDIN_FILENO, utils->outfile, STDOUT_FILENO);
	if (!env)
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
	if (env != NULL && env->str != NULL)
	{
		if (access(exec->cmd[0], X_OK) == 0)
			execve(exec->cmd[0], exec->cmd, NULL);
		else
			ft_constructor_cmd(exec);
	(void)export;
	}
	if (utils->infile != -1)
		close(utils->infile);
	if (utils->outfile != -1)
		close(utils->outfile);
}

void	dup_n_close(int infile_to_close, int infile_to_copy,
		int outfile_to_close, int outfile_to_copy)
{
	if (infile_to_close != -1)
	{
		dup2(infile_to_close, infile_to_close);
		close(infile_to_close);
	}
	if (outfile_to_close != -1)
	{
		dup2(outfile_to_close, outfile_to_copy);
		close(outfile_to_close);
	}
	(void)infile_to_copy;
}
