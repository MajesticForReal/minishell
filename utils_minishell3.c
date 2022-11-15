/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:59:29 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 18:13:54 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list_export_egal(t_env *env, t_exec *exec, t_utils *utils)
{
	if (utils->outfile != -1)
	{
		ft_putstr_fd("export ", utils->outfile);
		ft_putstr_fd(env->str, utils->outfile);
		ft_putstr_fd("\"\"", utils->outfile);
		ft_putstr_fd("\n", utils->outfile);
	}
	else
	{
		ft_putstr_fd("export ", exec->fd_cmd[1]);
		ft_putstr_fd(env->str, exec->fd_cmd[1]);
		ft_putstr_fd("\"\"", exec->fd_cmd[1]);
		ft_putstr_fd("\n", exec->fd_cmd[1]);
	}
}

void	ft_print_list_export_no_egal(t_env *env, t_exec *exec, t_utils *utils)
{
	if (utils->outfile != -1)
	{
		ft_putstr_fd("export ", utils->outfile);
		ft_putstr_fd(env->str, utils->outfile);
		ft_putstr_fd("\n", utils->outfile);
	}
	else
	{
		ft_putstr_fd("export ", exec->fd_cmd[1]);
		ft_putstr_fd(env->str, exec->fd_cmd[1]);
		ft_putstr_fd("\n", exec->fd_cmd[1]);
	}
}

void	ft_print_list_env(t_env *env, t_exec *exec, t_utils *utils)
{
	while (env != NULL)
	{
		if (utils->outfile != -1)
		{
			ft_putstr_fd(env->str, utils->outfile);
			ft_putstr_fd("\n", utils->outfile);
		}
		else
		{
			ft_putstr_fd(env->str, exec->fd_cmd[1]);
			ft_putstr_fd("\n", exec->fd_cmd[1]);
		}
		env = env->next;
	}
}

void	ft_all_builtin(t_lex *lex, t_utils *utils, t_exec *exec)
{
	if (exec != NULL && exec->cmd != NULL && exec->cmd[0] != NULL)
	{
		if (ft_compare(exec->cmd[0], "pwd") == SUCCESS)
			ft_builtin_pwd(1, exec, utils);
		else if (ft_compare(exec->cmd[0], "cd") == SUCCESS)
			ft_builtin_cd_all(lex, utils->env, utils, exec);
		else if (ft_compare(exec->cmd[0], "echo") == SUCCESS)
			ft_builtin_echo_all(lex, exec, utils);
		else if (ft_compare(exec->cmd[0], "env") == SUCCESS)
			ft_print_list_env(utils->env, exec, utils);
		else if (ft_compare(exec->cmd[0], "unset") == SUCCESS)
			ft_unset_var(lex, utils->env);
		else if (ft_compare(exec->cmd[0], "export") == SUCCESS)
			ft_export_var(lex, exec, utils);
	}
}

int	ft_check_builtin(t_exec *exec)
{
	if (exec != NULL && exec->cmd != NULL && exec->cmd[0] != NULL)
	{
		if (ft_compare(exec->cmd[0], "pwd") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "cd") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "echo") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "env") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "unset") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "export") == SUCCESS)
			return (SUCCESS);
	}
	return (-1);
}
