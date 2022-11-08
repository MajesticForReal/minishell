/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:56:30 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/08 22:39:38 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd_cmd(t_exec *exec)
{
	while (exec != NULL)
	{
		exec->fd_cmd[0] = STDIN_FILENO;
		exec->fd_cmd[1] = STDOUT_FILENO;
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return ;
}

void	ft_exec_pipe(t_exec *exec)
{
	ft_init_fd_cmd(exec);
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

int	ft_count_redir(t_exec *exec, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (exec->file[i])
	{
		if (exec->file[i][0] == c && exec->file[i][1] == '\0')
			nb++;
		i++;
	}
	return (nb);
}

int	ft_count_redir_toto(t_exec *exec, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (exec->file[i])
	{
		if (exec->file[i][0] == c && exec->file[i][1] == c)
			nb++;
		i++;
	}
	return (nb);
}

void	ft_open_toto(t_exec *exec, t_utils *utils)
{
	int	nb_in;

	nb_in = ft_count_redir_toto(exec, '>');
	utils->i = -1;
	while (exec->file[++utils->i] != NULL && nb_in > 0)
	{
		if (exec->file[utils->i][0] == '>' && exec->file[utils->i][1] == '>')
		{
			nb_in--;
			utils->outfile = open(exec->file[++utils->i],
									O_CREAT | O_WRONLY | O_APPEND,
									0644);
			if (utils->outfile < 0)
			{
				perror(exec->file[utils->i]);
				break ;
			}
			else if (nb_in != 0)
			{
				close(utils->outfile);
				utils->i++;
			}
		}
		else
			utils->i++;
	}
}

void	ft_open_in(t_exec *exec, t_utils *utils)
{
	int	nb_in;
	int	i;

	nb_in = ft_count_redir(exec, '<');
	i = -1;
	while (exec->file[++i] != NULL && nb_in > 0)
	{
		if (exec->file[i][0] == '<' && exec->file[i][1] == '\0')
		{
			nb_in--;
			utils->infile = open(exec->file[++i], O_RDONLY);
			if (utils->infile < 0)
			{
				perror(exec->file[i]);
				break ;
			}
			else if (nb_in != 0)
			{
				close(utils->infile);
				i++;
			}
		}
		else
			i++;
	}
}

void	ft_open_out(t_exec *exec, t_utils *utils)
{
	int	nb_in;
	int	i;

	nb_in = ft_count_redir(exec, '>');
	i = -1;
	printf("NB IN %d\n", nb_in);
	while (exec->file[++i] != NULL && nb_in > 0)
	{
		printf("DANS OUT\n");
		if (exec->file[i][0] == '>' && exec->file[i][1] == '\0')
		{
			nb_in--;
			utils->outfile = open(exec->file[++i], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
			if (utils->outfile < 0)
			{
				perror(exec->file[i]);
				break ;
			}
			else if (nb_in != 0)
			{
				close(utils->outfile);
				i++;
			}
		}
		else
			i++;
	}
}

void	ft_no_pipe_redir(t_exec *exec, t_utils *utils)
{
	while (exec != NULL && exec->file != NULL)
	{
		printf("DANS LE WHILE\n");
		ft_open_out(exec, utils);
		ft_open_in(exec, utils);
		ft_open_toto(exec, utils);
		if (exec->next != NULL)
			exec = exec->next;
		else
			break ;
	}
	return ;
}

void	ft_processus_no_pipe(t_exec *exec, t_utils *utils, t_env *env)
{
	// DUP AND CLOSE AVEC LE INFILE OU OUTFILE EN FONCTION DES REDIR QUE JAI
	// cmd constructor (ls -> /usr/bin/ls) 
	// check env if pas de env juste access et si pas d'access alors on return
	// if env valide on access et si pas daccess alors constructor
	// acesss cmd[0] pour voir chemin absol
	// constructor = 
	// EXECVE
}

void	ft_exec_no_pipe(t_exec *exec, t_lex *lex, t_env *env, t_utils *utils)
{
	ft_init_fd_cmd(exec);
	if (ft_check_builtin(exec) == -1)
	{
		printf("TOUJOURS ICI\n");
		ft_no_pipe_redir(exec, utils);
		// IF EXEC ./minishell
			-> FT_EXEC retirer "./" puis coller a tout le path en access,
			executer dans execve
		if (/*CMD EXISTANTE*/)
		{
			exec->process_id = fork();
			if (exec->process_id < 0)
				return (perror("Minishell: fork:"));
			else if (exec->process_id == 0))
				ft_processus_no_pipe();
			else
			{
				// ft_WAITPID + SIGNAUX
			}
		}
	}
	else if (ft_check_builtin(exec) == 1)
	{
		ft_no_pipe_redir(exec, utils);
		//EXEC BUILTIN ft_all_builtins
		//close infile et outfile
		// return;
	}
}

void	ft_exec(t_exec *exec, t_lex *lex, t_env *env, t_utils *utils)
{
	utils->infile = 0;
	utils->outfile = 0;
	if (exec->next == NULL)
	{
		printf("NOPIPE\n");
		ft_exec_no_pipe(exec, lex, env, utils);
	}
	else
		ft_exec_pipe(exec);
}