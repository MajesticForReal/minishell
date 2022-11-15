/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:31:30 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/15 18:28:28 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exec(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->str_cmd != NULL)
		free(exec->str_cmd);
	if (exec->heredoc != NULL)
		free(exec->heredoc);
	if (exec->cmd)
		free(exec->cmd);
	if (exec->path)
	{
		while (exec->path[i])
		{
			free(exec->path[i]);
			i++;
		}
		free(exec->path);
	}
	if (exec->file)
		free(exec->file);
}

void	ft_free_lex(t_lex *lex)
{
	t_lex	*tmp;

	while (lex != NULL)
	{
		if (lex->str != NULL)
			free(lex->str);
		if (lex->next != NULL)
		{
			tmp = lex;
			lex = lex->next;
			free(tmp);
		}
		else
		{
			free(lex);
			break ;
		}
	}
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp3;

	while (env != NULL)
	{
		if (env->str != NULL)
			free(env->str);
		if (env->next != NULL)
		{
			tmp3 = env;
			env = env->next;
			free(tmp3);
		}
		else
		{
			free(env);
			break ;
		}
	}
}

void	ft_free_export(t_utils *utils)
{
	t_env	*tmp3;

	while (utils->export != NULL)
	{
		if (utils->export->str != NULL)
			free(utils->export->str);
		if (utils->export->next != NULL)
		{
			tmp3 = utils->export;
			utils->export = utils->export->next;
			free(tmp3);
		}
		else
		{
			free(utils->export);
			break ;
		}
	}
}

void	ft_free_utils(t_utils *utils)
{
	if (utils != NULL)
	{
		if (utils->home_str != NULL)
			free(utils->home_str);
		free(utils);
	}
}
