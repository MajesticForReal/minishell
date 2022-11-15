/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:47:21 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 23:48:47 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_malloc_error(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

int	ft_count_words(const char *str, char c)
{
	int	i;
	int	j;
	int	first_letter;

	i = 0;
	j = 0;
	first_letter = 0;
	while (str[j] != '\0')
	{
		if (str[j] != c && first_letter == 0)
		{
			first_letter = 1;
			i++;
		}
		else if (str[j] == c)
			first_letter = 0;
		j++;
	}
	return (i);
}

void	ft_words_cpy(const char *s, int *start_w, int end, char *strs)
{
	int		i;

	i = 0;
	while (*start_w < end)
	{
		strs[i] = s[*start_w];
		i++;
		*start_w += 1;
	}
	strs[i] = '\0';
	*start_w = -1;
}

char	**ft_r_split(char const *s, char c, char **strs)
{
	size_t	i;
	size_t	j;
	int		start_w;

	i = 0;
	j = 0;
	start_w = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start_w < 0)
			start_w = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start_w >= 0)
		{
			strs[j] = malloc(sizeof(char) * ((i - start_w) + 1));
			if (strs[j] == NULL)
				return (ft_malloc_error(strs));
			ft_words_cpy(s, &start_w, i, strs[j]);
			j++;
		}
		i++;
	}
	strs[j] = '\0';
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	strs = NULL;
	if (s == NULL || s[0] == '\0')
		return (NULL);
	strs = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (strs == NULL)
		return (NULL);
	strs = ft_r_split(s, c, strs);
	return (strs);
}
