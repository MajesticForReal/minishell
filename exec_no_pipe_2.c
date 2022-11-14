/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:38:11 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/13 04:04:51 by anrechai         ###   ########.fr       */
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

void	ft_exec_no_pipe(t_exec *exec, t_env *env, t_utils *utils, t_lex *lex, t_env *export)
{
	ft_init_fd_cmd_no_pipe(exec);
	if (ft_no_pipe_redir(exec, utils) == EXIT_FAILURE)
		return ;
	if (exec->cmd[0] != NULL && ft_check_builtin(exec) == -1)
	{
		exec->process_id = fork();
		if (exec->process_id < 0)
			return (perror("minishell: fork:"));
		signal(SIGINT, ft_detect_sig);
		signal(SIGQUIT, ft_detect_sig);
		if (exec->process_id == 0 && exec->cmd != NULL && exec->cmd[0][0] == '.'
			&& exec->cmd[0][1] == '/')
			ft_exec_prog(exec);
		else if (exec->process_id == 0)
			ft_processus_no_pipe(exec, env, utils);
		else
			waitpid(exec->process_id, 0, 0);
	}
	else if (exec->cmd[0] != NULL && ft_check_builtin(exec) == 1)
	{
		exec_builtin_no_pipe(exec, utils, lex, env, export);
		return ;
	}
}

void	exec_builtin_no_pipe(t_exec *exec, t_utils *utils, t_lex *lex,
		t_env *env, t_env *export)
{
	ft_all_builtin(lex, env, utils, exec, export);
	ft_close_files(utils->infile, utils->outfile);
}

void	ft_close_files(int infile, int outfile)
{
	if (infile != -1)
		close(infile);
	if (outfile != -1)
		close(outfile);
}
