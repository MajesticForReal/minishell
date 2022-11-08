/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:59:04 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/08 21:50:57 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_compare(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] == str2[i])
	{
		if (str[i] == '\0' && str2[i] == '\0')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

void	ft_init_fill_str_home(char *complet_str, t_utils *utils)
{
	int	i;
	int	j;

	i = 5;
	j = 0;
	utils->i = 0;
	utils->home_str = malloc(sizeof(char) * ft_strlen(complet_str) - 4);
	if (utils->home_str == NULL)
		return ;
	while (complet_str[i] != '\0')
	{
		utils->home_str[j] = complet_str[i];
		i++;
		j++;
	}
	utils->home_str[j] = '\0';
}
