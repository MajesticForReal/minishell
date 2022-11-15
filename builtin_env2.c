/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:05:39 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 17:19:40 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_first_is_alpha(char *lex_str)
{
	if (lex_str != NULL && lex_str[0] != '\0')
	{
		if ((lex_str[0] <= 'z' && lex_str[0] >= 'a') || (lex_str[0] >= 'A'
				&& lex_str[0] <= 'Z') || (lex_str[0] == '_'))
			return (SUCCESS);
		else
			return (FAIL);
	}
	return (FAIL);
}

int	ft_detect_special_char_export(char *lex_str)
{
	int	i;

	i = 0;
	while (lex_str[i] != '\0')
	{
		if (lex_str[i] < '0')
			return (FAIL);
		if (lex_str[i] > 'z')
			return (FAIL);
		if (lex_str[i] > '9' && lex_str[i] < '=')
			return (FAIL);
		if (lex_str[i] > '=' && lex_str[i] < 'A')
			return (FAIL);
		if (lex_str[i] > 'Z' && lex_str[i] < '_')
			return (FAIL);
		if (lex_str[i] > '_' && lex_str[i] < 'a')
			return (FAIL);
		if (lex_str[i] == '=' && lex_str[i] != lex_str[0])
			return (SUCCESS);
		i++;
	}
	return (SUCCESS);
}

int	ft_str_have_egal(char *lex_str)
{
	int	i;

	i = 0;
	while (lex_str[i] != '\0')
	{
		if (lex_str[i] == '=')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	ft_check_valid_export_env(char *lex_str)
{
	if (ft_first_is_alpha(lex_str) == SUCCESS
		&& ft_str_have_egal(lex_str) == SUCCESS
		&& ft_detect_special_char_export(lex_str) == SUCCESS)
		return (1);
	if (ft_first_is_alpha(lex_str) == SUCCESS
		&& ft_detect_special_char_export(lex_str) == SUCCESS)
		return (2);
	else
		return (0);
}
