/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:55:25 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/15 19:01:09 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_lex **lex, t_utils **utils, char **envp)
{
	(*lex) = malloc(sizeof(t_lex));
	if (!(*lex))
		return (-1);
	(*lex)->str = NULL;
	(*lex)->next = NULL;
	return (0);
}

int	ft_init2(t_lex **lex, t_utils **utils, t_exec **exec)
{
	(*exec) = malloc(sizeof(t_exec));
	if (!(*exec))
	{
		free((*utils));
		free((*lex));
		return (-1);
	}
	(*exec)->str_cmd = NULL;
	(*exec)->heredoc = NULL;
	(*exec)->next = NULL;
	(*exec)->cmd = NULL;
	(*exec)->path = NULL;
	(*exec)->file = NULL;
	return (0);
}

void	ft_exit(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	ft_free(lex, env, utils, exec);
	exit(EXIT_SUCCESS);
}
