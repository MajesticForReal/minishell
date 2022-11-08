/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:51:31 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/08 21:34:28 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_next_lex_to_noword(t_lex *lex)
{
	int	i;

	i = 0;
	while(lex != NULL && lex->token != TOK_WORD)
	{
		lex = lex->next;
		i++;
	}
	return (i);
}

void	ft_bzero_exec(t_exec *exec)
{
	exec = malloc(sizeof(t_exec));
	if(exec == NULL)
		return ;
		
	exec->cmd = NULL;
	exec->str_cmd = NULL;
	exec->path = NULL;
	exec->file = NULL;
	exec->nb_option = 0;
	exec->cmd_size = 0;
	exec->token_before = 0;
	exec->next = NULL;
}

char	*ft_find_path(t_env *env)
{
	char *str;

	str = NULL;
	while(env != NULL)
	{
		if(env->str[0] == 'P' && env->str[1] == 'A'
			&& env->str[2] == 'T' && env->str[3] == 'H'
			&& env->str[4] == '=')
				str = env->str + 5;
		if(env->next != NULL)
			env = env->next;
		else
			break ;
	}
	return (str);
}

void	ft_malloc_heredoc_str(t_exec *exec)
{
	int	i;
	char *str;
	
	str = ".HEREDOC";
	i = 0;
	i = ft_strlen(".HERDOC");
	exec->heredoc = malloc(sizeof(char *) * i + 1);
	if(exec->heredoc == NULL)
		return ;
	i = 0;
	while(str[i] != '\0')
	{
		exec->heredoc[i] = str[i];
		i++;
	}
	exec->heredoc[i] = '\0';
}

void	ft_next_exec(t_exec *exec)
{
	t_exec	*new;

	new = ft_initialize_struct_exec();
	exec->next = new;
	return ;
}

t_exec	*ft_initialize_struct_exec(void)
{
	t_exec	*curr;

	curr = malloc(sizeof(t_exec));
	if (!curr)
		return (NULL);
	curr->next = NULL;
	curr->token_before = -1;
	curr->cmd = NULL;
	curr->redir = NULL;
	return (curr);
}
