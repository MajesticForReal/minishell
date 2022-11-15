/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:58:03 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/16 00:25:38 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy_lex_str_to_export_1(char *env_str, int *i)
{
	char	*str_w_quotes;

	str_w_quotes = NULL;
	if (env_str == NULL || env_str[0] == '\0')
		return (NULL);
	*i = ft_strlen(env_str) + 3;
	str_w_quotes = malloc(sizeof(char) * (*i));
	if (str_w_quotes == NULL)
		return (NULL);
	*i = 0;
	return (str_w_quotes);
}

void	ft_copy_lex_str_to_export_3(int *j, int *i)
{
	*i = *i + 1;
	*j = *j + 1;
}

void	ft_copy_lex_str_to_export_2(char *str_w_quotes,
int *j, int *i, int *trigger)
{
	*j = *j + 1;
	str_w_quotes[*j] = '"';
	*i = *i + 1;
	*j = *j + 1;
	*trigger = *trigger + 1;
}

char	*ft_copy_lex_str_to_export(char *env_str)
{
	int		i;
	int		j;
	int		trigger;
	char	*str_w_quotes;

	trigger = 0;
	j = 0;
	str_w_quotes = ft_copy_lex_str_to_export_1(env_str, &i);
	while (env_str[i] != '\0')
	{
		str_w_quotes[j] = env_str[i];
		if (env_str[i] == '=' && trigger == 0 && env_str[i + 1] != '"')
			ft_copy_lex_str_to_export_2(str_w_quotes, &j, &i, &trigger);
		else
			ft_copy_lex_str_to_export_3(&j, &i);
	}
	if (env_str[i - 1] != '"' && trigger != 0)
	{
		str_w_quotes[j] = '"';
		str_w_quotes[j + 1] = '\0';
	}
	else
		str_w_quotes[j] = '\0';
	return (str_w_quotes);
}

void	ft_add_back_str_export(t_env *export, char *str)
{
	t_env	*new_export;
	t_env	*export_cpy;
	char	*export_str;

	export_str = ft_copy_lex_str_to_export(str);
	export_cpy = export;
	new_export = ft_init_env();
	while (export_cpy != NULL)
	{
		if (ft_compare_stop_egal(export_cpy->str, export_str) == SUCCESS)
		{
			ft_replace_t_export(export_cpy, export_str);
			export = export_cpy;
			return ;
		}
		export_cpy = export_cpy->next;
	}
	while (export->next != NULL)
		export = export->next;
	export->next = new_export;
	new_export->str = export_str;
}
