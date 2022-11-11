/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:19:02 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/10 20:38:57 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_toto(t_exec *exec, t_utils *utils)
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
				return (EXIT_FAILURE);
			}
			else if (nb_in != 0)
				close(utils->outfile);
		}
		else
			utils->i++;
	}
	return (EXIT_SUCCESS);
	// IF PERROR -> FT_EXIT
}

int	ft_open_in(t_exec *exec, t_utils *utils)
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
				return (EXIT_FAILURE);
			}
			else if (nb_in != 0)
				close(utils->infile);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
	// IF PERROR -> FT_EXIT
}

int	ft_open_out(t_exec *exec, t_utils *utils)
{
	int	nb_in;
	int	i;

	nb_in = ft_count_redir(exec, '>');
	i = -1;
	while (exec->file[++i] != NULL && nb_in > 0)
	{
		if (exec->file[i][0] == '>' && exec->file[i][1] == '\0')
		{
			nb_in--;
			utils->outfile = open(exec->file[++i], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
			if (utils->outfile < 0)
			{
				perror(exec->file[i]);
				return (EXIT_FAILURE);
			}
			else if (nb_in != 0)
				close(utils->outfile);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
	// IF PERROR -> FT_EXIT
}
