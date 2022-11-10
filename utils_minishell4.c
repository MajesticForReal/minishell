/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:20:30 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/09 15:35:40 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat_path(char *dest, char *src)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src) + 2));
	if (!new_str)
		return (NULL);
	while (dest[i])
	{
		new_str[i] = dest[i];
		i++;
	}
	new_str[i] = '/';
	i++;
	while (src[j])
	{
		new_str[i] = src[j];
		j++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		s_len;
	int		i;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	i = 0;
	dest = malloc((s_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup_prog(const char *s)
{
	char	*dest;
	int		s_len;
	int		i;
	int		j;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	s_len--;
	s_len--;
	i = 0;
	j = 2;
	dest = malloc((s_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
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
