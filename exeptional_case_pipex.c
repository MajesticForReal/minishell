/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeptional_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:23:37 by klaurier          #+#    #+#             */
/*   Updated: 2022/06/23 14:43:39 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_exeptional_case_1(t_pipex *pipex, char **argv)
{
	if ((argv[2][0] == '\0' || ft_detect_exeptional_case_1(argv) == 1)
		&& (argv[3][0] == '\0' || ft_detect_exeptional_case_2(argv) == 1))
	{
		write(2, " : command not found\n", 22);
		write(2, " : command not found\n", 22);
		free(pipex);
		return ;
	}
	if (argv[3][0] == '\0')
	{
		write(2, " : command not found\n", 22);
		free(pipex);
		return ;
	}
	return ;
}

int	ft_detect_exeptional_case_0(char **argv, t_pipex *pipex)
{
	if (argv[3][0] == '\0')
		return (1);
	if (argv[2][0] == '\0')
	{
		ft_malloc_nothing(pipex);
		if (ft_detect_exeptional_case_2(argv) == 1)
			pipex->cmd2 = ft_split(argv[3], 'a');
		else
			pipex->cmd2 = ft_split(argv[3], ' ');
	}
	return (0);
}

int	ft_detect_exeptional_case_3(int i, int j)
{
	if (i == 1 && j == 1)
		return (3);
	else if (i == 0 && j == 1)
		return (2);
	else if (i == 1 && j == 0)
		return (1);
	else
		return (0);
}

int	ft_detect_exeptional_case_2(char **argv)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	if (argv[3][0] != '\0')
	{
		while (argv[3][++i] != '\0')
			if (argv[3][i] == ' ')
				j++;
		if (j == i)
			k = 1;
	}
	if (k == 1)
		return (1);
	else
		return (0);
}

int	ft_detect_exeptional_case_1(char **argv)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	if (argv[2][0] != '\0')
	{
		while (argv[2][++i] != '\0')
			if (argv[2][i] == ' ')
				j++;
		if (j == i)
			k = 1;
	}
	if (k == 1)
		return (1);
	else
		return (0);
}
