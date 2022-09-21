/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:34:36 by klaurier          #+#    #+#             */
/*   Updated: 2022/06/22 17:27:33 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		x;
	char	*str;

	x = 0;
	while (src[x] != '\0')
		x++;
	str = (char *)malloc(sizeof(char) * (x + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < x)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (((char *)str) + i);
		i++;
	}
	if (c == 0)
		return (((char *)str) + i);
	return (NULL);
}

char	*ft_strcat_cmd(char *path, char *cmd, char slash)
{
	int		i;
	int		j;
	char	*complet_path;

	i = -1;
	j = 0;
	complet_path = NULL;
	complet_path = malloc(sizeof(char) * ft_strlen(cmd) + ft_strlen(path) + 2);
	if (complet_path == NULL)
		return (NULL);
	while (path[++i] != '\0')
		complet_path[i] = path[i];
	complet_path[i] = slash;
	i++;
	while (cmd[j] != '\0')
	{
		complet_path[i] = cmd[j];
		i++;
		j++;
	}
	complet_path[i] = '\0';
	return (complet_path);
}