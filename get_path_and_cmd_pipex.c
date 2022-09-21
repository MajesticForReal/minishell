/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_and_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:36:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/06/23 13:36:19 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"minishell.h"

void	ft_malloc_nothing(t_pipex *pipex)
{
	char	*str;
	int		i;

	i = 0;
	str = " ";
	pipex->cmd1 = malloc(sizeof(char *) * 2);
	if (pipex->cmd1 == NULL)
		return ;
	pipex->cmd1[0] = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (pipex->cmd1 == NULL)
		return ;
	while (str[i] != '\0')
	{
		pipex->cmd1[0][i] = str[i];
		i++;
	}
	pipex->cmd1[0][i] = '\0';
	pipex->cmd1[1] = NULL;
}

int	ft_get_path_cmd(char **argv, char **envp, t_pipex *pipex)
{
	const char	*s;

	s = ft_search_line_path(envp);
	pipex->path = ft_split(s + (5 * (s != NULL)), ':');
	return (0);
	(void)argv;
}

int	ft_get_cmd(char **argv, t_pipex *pipex)
{
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->cmd1 = ft_split(argv[2], ' ');
	return (0);
}

const char	*ft_search_line_path(char **envp)
{
	const char	*line_path;
	int			i;
	int			j;

	line_path = "PATH=";
	i = 0;
	j = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		while (envp[i][j] == line_path[j] && envp[i][j] != '\0')
		{
			if (j == 4)
				return (envp[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
