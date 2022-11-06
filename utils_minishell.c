/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:19:32 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/06 20:59:32 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_compare_just_a_part(char *complet_str, char *str_part,
		t_utils *utils)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = ft_strlen(str_part);
	while (complet_str[i] != '\0')
	{
		while (complet_str[i] == str_part[j])
		{
			if (j == k - 1)
			{
				ft_init_fill_str_home(complet_str, utils);
				return ;
			}
			j++;
			i++;
		}
		j = 0;
		i++;
	}
}

char	*ft_concat2(char *str_1, char *str_2)
{
	char	*new_str;
	int		i;
	int		k;

	i = -1;
	k = 0;
	new_str = malloc(sizeof(char) * ft_strlen(str_1) + ft_strlen(str_2) + 1);
	if (new_str == NULL)
		return (NULL);
	while (str_1[++i] != '\0')
	{
		new_str[k] = str_1[i];
		k++;
	}
	i = 0;
	while (str_2[i] != '\0')
	{
		new_str[k] = str_2[i];
		i++;
		k++;
	}
	new_str[k] = '\0';
	free(str_1);
	free(str_2);
	return (new_str);
}

int	ft_print_2_d_tab(char **strs, int index)
{
	if (strs == NULL)
		return (FAIL);
	else
	{
		while (strs[index] != NULL)
		{
			if (strs[index + 1] == NULL)
			{
				ft_putstr_fd(strs[index], 1);
				return (1);
			}
			ft_putstr_fd(strs[index], 1);
			ft_putchar_fd(' ', 1);
			index++;
		}
	}
	return (SUCCESS);
}

void	ft_print_list_env(t_env *env)
{
	while (env != NULL)
	{
		ft_putstr_fd(env->str, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

void	ft_print_lex_k(t_lex *lex)
{
	int	i;

	i = 0;
	printf("\n----lexer----\n");
	printf("--begin--\n");
	if (lex == NULL)
	{
		printf("lex == NULL\n");
		printf("----end----\n\n");
		return ;
	}
	else
		printf("lex != NULL\n");
	while (lex->next != NULL)
	{
		printf("%d = tokken: %d / STR: %s\n", i, lex->token, lex->str);
		if (lex->next != NULL)
			lex = lex->next;
		i++;
	}
	if (lex != NULL)
	{
		printf("%d = tokken: %d / STR: %s\n", i, lex->token, lex->str);
		printf("----end----\n\n");
	}
}
