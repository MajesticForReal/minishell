/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:18:23 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/10 21:26:06 by anrechai         ###   ########.fr       */
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

void	ft_exec_no_pipe(t_exec *exec, t_env *env, t_utils *utils, t_lex *lex)
{
	ft_init_fd_cmd(exec);
	if (ft_no_pipe_redir(exec, utils) == EXIT_FAILURE)
		return ;
	if (ft_check_builtin(exec) == -1)
	{
			exec->process_id = fork();
			if (exec->process_id < 0)
				return (perror("minishell: fork:"));
			// SIGNAUX
			// signal(SIGQUIT, handle_sig_child);
			// signal(SIGINT, handle_sig_child);
			if (exec->process_id== 0 && exec->cmd != NULL && exec->cmd[0][0] == '.'
				&& exec->cmd[0][1] == '/')
					ft_exec_prog(exec);
			else if (exec->process_id == 0)
				ft_processus_no_pipe(exec, env, utils);
			else
				waitpid(exec->process_id, 0, 0);
	}
	else if (ft_check_builtin(exec) == 1)
	{
		// STDOUT_FILENO = utils->outfile;
		// if (utils->infile != -1)
		// {
		// 	dup2(utils->infile, STDIN_FILENO);
		// 	close(utils->infile);
		// }
		// if (utils->outfile != -1)
		// {
		// 	dup2(utils->outfile, STDOUT_FILENO);
		// 	close(utils->outfile);
		// }
		ft_all_builtin(lex, env, utils);
		// if (STDOUT_FILENO != -1)
		// {
		// 	dup2(STDOUT_FILENO, utils->outfile);
		// 	close(STDOUT_FILENO);
		// }
		// exec->fd_cmd[0] = STDIN_FILENO;
		// exec->fd_cmd[1] = STDOUT_FILENO;
		// close (exec->fd_cmd[0]);
		// close (exec->fd_cmd[1]);
		if (utils->infile != -1)
			close(utils->infile);
		if (utils->outfile!= -1)
			close(utils->outfile);
		return ;
	}
//faire tous les builtins dans fd_cmd[1], parce que c'est le seul dans le code qui a la bonne sortie d'ecriture -> outfile + pipe ou stdout + pipe ?
}

int	ft_no_pipe_redir(t_exec *exec, t_utils *utils)
{
	while (exec != NULL && exec->file != NULL)
	{
		// faire les return de out et toto
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

void	ft_processus_no_pipe(t_exec *exec, t_env *env, t_utils *utils)
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
	}
}
