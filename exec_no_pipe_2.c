/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:38:11 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/16 00:33:49 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redir(t_exec *exec, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (exec != NULL && exec->file != NULL && exec->file[i])
	{
		if (exec->file[i][0] == c && exec->file[i][1] == '\0')
			nb++;
		i++;
	}
	return (nb);
}

void	ft_exec_no_pipe(t_exec *exec, t_utils *utils, t_lex *lex)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	ft_init_fd_cmd_no_pipe(exec);
	if (ft_no_pipe_redir(exec, utils) == EXIT_FAILURE)
		return ;
	if (exec->cmd[0] != NULL && ft_check_builtin(exec) == -1)
		exec_cmd_no_pipe(exec, utils, lex);
	else if (exec->cmd[0] != NULL && ft_check_builtin(exec) == 1)
	{
		ft_all_builtin(lex, utils, exec);
		ft_close_files(utils->infile, utils->outfile);
		return ;
	}
}

void	exec_cmd_no_pipe(t_exec *exec, t_utils *utils, t_lex *lex)
{
	exec->process_id = fork();
	if (exec->process_id < 0)
		return (perror("minishell: fork:"));
	signal(SIGINT, ft_detect_sig_child);
	signal(SIGQUIT, ft_detect_sig_child);
	if (exec->process_id == 0 && exec->cmd != NULL && exec->cmd[0][0] == '.'
		&& exec->cmd[0][1] == '/')
		ft_exec_prog(exec);
	else if (exec->process_id == 0)
		ft_processus_no_pipe(lex, exec, utils);
	else
	{
		waitpid(exec->process_id, &g_exstat, 0);
		if (WIFEXITED(g_exstat))
			g_exstat = WEXITSTATUS(g_exstat);
		else if (WIFSIGNALED(g_exstat))
			g_exstat = WTERMSIG(g_exstat) + 128;
	}
}

void	ft_close_files(int infile, int outfile)
{
	if (infile != -1)
		close(infile);
	if (outfile != -1)
		close(outfile);
}
