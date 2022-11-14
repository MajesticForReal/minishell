/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_k.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:02:36 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/14 23:16:34 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compare_just_a_part_2(char *var_more)
{
	int		i;
	int		j;
	char	*var_only;

	i = 0;
	j = -1;
	if (var_more == NULL)
		return (FAIL);
	var_only = NULL;
	while ((var_more[i] <= 'z' && var_more[i] >= 'a') || (var_more[i] <= 'Z'
			&& var_more[i] >= 'A') || (var_more[i] <= '9' && var_more[i] >= '0')
		|| var_more[i] == '_')
		i++;
	var_only = malloc(sizeof(char) * (i + 1));
	if (var_only == NULL)
		return (FAIL);
	while (++j < i)
		var_only[j] = var_more[j];
	var_only[j] = '\0';
	return (ft_var_in_env(var_only));
}

int	ft_var_in_env(char *var_only)
{
	if (getenv(var_only) != NULL)
	{
		free(var_only);
		return (SUCCESS);
	}
	else
	{
		free(var_only);
		return (FAIL);
	}
}

void	ft_change_doll_egal(t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	free(lex->str);
	lex->str = malloc(sizeof(char) * (ft_strlen(lex->next->str) + 2));
	if (lex->str == NULL)
		return ;
	lex->str[0] = '$';
	if (lex->next != NULL)
	{
		while (lex->next->str[i] != '\0')
		{
			lex->str[j] = lex->next->str[i];
			i++;
			j++;
		}
		lex->str[j] = '\0';
	}
	ft_free_doll_egal(lex);
}

void	ft_free_doll_egal(t_lex *lex)
{
	t_lex	*tmp;

	if (lex == NULL)
		return ;
	if (lex->next->next != NULL)
	{
		tmp = lex->next;
		lex->next = lex->next->next;
		free(tmp->str);
		free(tmp);
	}
	else
	{
		tmp = lex->next;
		lex->next = NULL;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_free_write_var_fd(char *concat, char *str, int fd)
{
	ft_putstr_fd(concat, fd);
	ft_putstr_fd("\n", fd);
	free(concat);
	free(str);
}
