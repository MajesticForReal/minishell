/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:56:30 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/12 02:24:34 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd_cmd(t_exec *exec)
{
	while (exec != NULL && exec->cmd[0] != NULL)
	{
		exec->fd_cmd[0] = dup(STDIN_FILENO);
		exec->fd_cmd[1] = dup(STDOUT_FILENO);
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return ;
}

void	ft_init_fd_cmd_no_pipe(t_exec *exec)
{
	while (exec != NULL && exec->cmd[0] != NULL)
	{
		exec->fd_cmd[0] = dup(STDIN_FILENO);
		exec->fd_cmd[1] = dup(STDOUT_FILENO);
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return ;
}

void	ft_constructor_cmd(t_exec *exec)
{
	int		i;
	char	*new_path;
	char	*my_cmd;
	char	*cmd_base;

	cmd_base = ft_strdup(exec->cmd[0]);
	new_path = NULL;
	my_cmd = ft_strdup(exec->cmd[0]);
	i = 0;
	if (ft_check_str(cmd_base, 2) == -1)
	{
		write(2, cmd_base, ft_strlen(cmd_base));
		write(2, ": No such file or directory\n", 28);
		free(my_cmd);
		free(cmd_base);
		return ;
	}
	while (exec->path && exec->path[i])
	{
		free(new_path);
		new_path = NULL;
		new_path = ft_strcat_path(exec->path[i], my_cmd);
		if (new_path == NULL)
			return ;
		exec->cmd[0] = new_path;
		if (access(new_path, X_OK) == 0)
			execve(new_path, exec->cmd, NULL);
		i++;
	}
	write(2, cmd_base, ft_strlen(cmd_base));
	write(2, ": command not found\n", 20);
	free(new_path);
	free(my_cmd);
	free(cmd_base);
}

int	ft_check_str(char *str, int i)
{
	DIR	*d;

	if (i == 1)
	{
		d = opendir(str);
		if (d == NULL)
			return (0);
		closedir(d);
		return (-1);
	}
	else if (i == 2)
		if (ft_strchr(str, '/') != NULL)
			return (-1);
	return (0);
}

void	ft_exec_prog_cwd(t_exec *exec, char *cmd_base)
{
	char	*tmp;
	char	*buf;
	size_t	size;

	size = 0;
	tmp = NULL;
	buf = NULL;
	tmp = getcwd(buf, size);
	free(exec->cmd[0]);
	exec->cmd[0] = NULL;
	buf = ft_strcat_path(tmp, cmd_base + 2);
	exec->cmd[0] = buf;
	if (access(exec->cmd[0], X_OK) == 0)
	{
		execve(exec->cmd[0], exec->cmd, NULL);
	}
	free(buf);
	free(tmp);
	return ;
}

void	ft_exec_prog(t_exec *exec)
{
	int		i;
	char	*new_path;
	char	*my_cmd;
	char	*cmd_base;

	cmd_base = ft_strdup(exec->cmd[0]);
	new_path = NULL;
	my_cmd = ft_strdup(exec->cmd[0] + 2);
	i = -1;
	if (ft_check_str(cmd_base, 1) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_base, ft_strlen(cmd_base));
		write(2, ": Is a directory\n", 17);
		return ;
	}
	while (exec->path && exec->path[++i])
	{
		free(new_path);
		new_path = NULL;
		new_path = ft_strcat_path(exec->path[i], my_cmd);
		if (new_path == NULL)
			return ;
		exec->cmd[0] = new_path;
		if (access(new_path, X_OK) == 0)
		{
			write(2, cmd_base, ft_strlen(cmd_base));
			write(2, ": No such file or directory\n", 28);
			free(my_cmd);
			free(cmd_base);
			return ;
		}
	}
	ft_exec_prog_cwd(exec, cmd_base);
	write(2, cmd_base, ft_strlen(cmd_base));
	write(2, ": command not found\n", 20);
	free(my_cmd);
	free(cmd_base);
}

void	ft_exec(t_exec *exec, t_env *env, t_utils *utils, t_lex *lex)
{
	utils->infile = -1;
	utils->outfile = -1;
	if (exec->next == NULL)
	{
		ft_exec_no_pipe(exec, env, utils, lex);
	}
	else if (exec->next != NULL)
	{
		ft_exec_pipe(exec, utils, env, lex);
		ft_waitpid(exec);
	}
	if (exec->cmd[0] != NULL && exec->fd_cmd[0] != STDIN_FILENO)
		close(exec->fd_cmd[0]);
	if (exec->cmd[0] != NULL && exec->fd_cmd[1] != STDOUT_FILENO)
		close(exec->fd_cmd[1]);
	return ;
}

void	ft_waitpid(t_exec *exec)
{
	while (exec->next != NULL && exec->next->cmd[0] != NULL)
	{
		if (ft_check_builtin(exec) != 1)
			waitpid(exec->process_id, 0, 0);
		// if (WIFEXITED(g_status))
		// 	g_status = WEXITSTATUS(g_status);
		// else if (WIFSIGNALED(g_status))
		// 	g_status = WTERMSIG(g_status) + 128;
		// SIGNAUX
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, handle_sig_parent);
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return ;
}