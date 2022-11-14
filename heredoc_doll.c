/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_doll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:10:24 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/14 23:15:27 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar_heredoc(char *input, int fd)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == '$')
		{
			if (ft_compare_just_a_part_2(input + i + 1) == SUCCESS)
			{
				k = 1;
				while (input[++j] != '\0' && input[j] != '$')
					write(fd, &input[j], 1);
				ft_write_var_env_in_fd(input + i + 1, fd);
			}
		}
	}
	if (k == 0)
	{
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
	}
}

void	ft_write_var_env_in_fd(char *input, int fd)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] <= 'z' && input[i] >= 'a')
			i++;
		else if (input[i] <= 'Z' && input[i] >= 'A')
			i++;
		else if (input[i] <= '9' && input[i] >= '0')
			i++;
		else if (input[i] == '_')
			i++;
		else
			break ;
	}
	ft_write_var_env_in_fd2(input, fd, i);
}

void	ft_write_var_env_in_fd2(char *input, int fd, int i)
{
	char	*str;
	char	*getenv_result;
	char	*concat;
	int		j;
	int		k;

	j = -1;
	k = 0;
	concat = NULL;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return ;
	while (++j < i)
		str[j] = input[j];
	str[j] = '\0';
	getenv_result = getenv(str);
	j = 0;
	k = i;
	i--;
	while (input[++i] != '\0')
		j++;
	concat = ft_write_var_env_in_fd3(concat, getenv_result, k, j, input);
	ft_free_write_var_fd(concat, str, fd);
}

char	*ft_write_var_env_in_fd3(char *concat, char *getenv_result, int k, int j, char *input)
{
	int	i;
	
	concat = malloc(sizeof(char) * (j + ft_strlen(getenv_result) + 1));
	if (concat == NULL)
		return NULL;
	i = -1;
	j = 0;
	while (getenv_result[++i] != '\0')
		concat[i] = getenv_result[i];
	while (input[k] != '\0')
	{
		concat[i] = input[k];
		i++;
		k++;
	}
	concat[i] = '\0';
	return (concat);
}
