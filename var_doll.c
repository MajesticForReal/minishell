/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_doll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:15:21 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/08 22:52:15 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cut_var_more(char *var_more)
{
	int		i;
	int		j;
	char	*var_only;

	i = 0;
	j = -1;
	var_only = NULL;
	while ((var_more[i] <= 'z' && var_more[i] >= 'a') || (var_more[i] <= 'Z'
			&& var_more[i] >= 'A') || (var_more[i] <= '9'
			&& var_more[i] >= '0'))
		i++;
	var_only = malloc(sizeof(char) * i + 1);
	if (var_only == NULL)
		return (NULL);
	while (++j < i)
		var_only[j] = var_more[j];
	var_only[j] = '\0';
	if (getenv(var_only) != NULL)
		return (var_only);
	else
	{
		free(var_only);
		return (NULL);
	}
}

int	ft_shearch_var(char *lex_str, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(lex_str);
	while (env != NULL)
	{
		while (env->str[i] != '\0' && env->str[i] != '=')
		{
			if (env->str[i] == lex_str[i])
				i++;
			else
				break ;
		}
		if (j == i)
			return (SUCCESS);
		i = 0;
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	return (FAIL);
}

int	ft_char_after_var(t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((lex->next->str[i] <= 'z' && lex->next->str[i] >= 'a')
		|| (lex->next->str[i] <= 'Z' && lex->next->str[i] >= 'A')
		|| (lex->next->str[i] <= '9' && lex->next->str[i] >= '0'))
		i++;
	while (lex->next->str[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);
}

void	ft_change_list_to_var(t_lex *lex)
{
	int		i;
	int		j;
	char	*tmp_var;
	t_lex	*tmp;

	tmp = NULL;
	i = 0;
	j = (ft_last_alpha_num(lex) - 1);
	i = ft_strlen(getenv(ft_cut_var_more(lex->next->str)));
	i = i + ft_char_after_var(lex);
	tmp_var = getenv(ft_cut_var_more(lex->next->str));
	lex->str = malloc(sizeof(char) * i + 1);
	if (lex->str == NULL)
		return ;
	lex->token = TOK_WORD;
	i = -1;
	while (tmp_var[++i] != '\0')
		lex->str[i] = tmp_var[i];
	while (lex->next->str[++j] != '\0')
	{
		lex->str[i] = lex->next->str[j];
		i++;
	}
	lex->str[i] = '\0';
	ft_free_tmp_list_to_var(lex, tmp);
}

void	ft_free_tmp_list_to_var(t_lex *lex, t_lex *tmp)
{
	if (lex->next->next != NULL)
	{
		tmp = lex->next;
		lex->next = lex->next->next;
		free(tmp->str);
		free(tmp);
		return ;
	}
	else
	{
		tmp = lex->next;
		lex->next = NULL;
		free(tmp->str);
		free(tmp);
		return ;
	}
}
