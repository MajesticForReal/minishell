/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:41:14 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/08 21:59:49 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	t_lex	*tmp;
	t_env	*tmp2;
	// int	i;

	while (lex != NULL && lex->next != NULL)
	{
		tmp = lex;
		if (lex->next != NULL)
			lex = lex->next;
		free(tmp->str);
		free(tmp);
	}
	free(lex->str);
	free(lex);
	while (env != NULL && env->next != NULL)
	{
		tmp2 = env;
		if (env->next != NULL)
			env = env->next;
		free(tmp2->str);
		free(tmp2);
	}
	free(env->str);
	free(env);
	if (utils->home_str != NULL)
		free(utils->home_str);
	free(utils);
	// i = 0;
	// while (exec != NULL)
	// {
	// 	free(exec->cmd);
	// i = 0;
	// while (exec->file != NULL)
	// {
	// 	free(exec->file[i]);
	// 	i++;
	// }
	// free(exec->file);
	// 	exec = exec->next;
	// }
	// free(exec);
	(void)exec;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_lex	*lex;
	t_env	*env;
	char	*input;
	t_utils	*utils;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	utils = malloc(sizeof(t_utils));
	utils->home_str = NULL;
	env = ft_init_fill_env(envp);
	lex = malloc(sizeof(t_lex));
	input = NULL;
	while (1)
	{
		input = readline(">");
		add_history(input);
		ft_lexer(input, lex);
		if (ft_parser_k(lex, env) == 0) // $ + quotes
		{
			ft_organizer(&lex); //virer espace et quotes
			if (ft_parser(lex) == 0)
			{
				ft_organizer_exec(lex, exec, env);
				ft_exec(exec, lex, env, utils);
			}
		}
		ft_print_exec(exec);
		// EXECVE
		// SIGNAUX
		// RETOUR ERREUR VARIABLE GLOBALE
		free(input);
		// ft_free(lex, env, utils, exec);
		// return (0);
	}
	(void)exec;
	(void)env;
	(void)input;
	(void)argc;
	(void)argv;
}

void	ft_print_exec(t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (exec != NULL)
	{
		while (exec != NULL)
		{
			printf("---- EXEC %d ----\n", j);
			if (exec->cmd != NULL)
			{
				while (exec->cmd[i] != NULL)
				{
					printf("CMD %d : %s\n", i, exec->cmd[i]);
					// free(exec->cmd[i]);
					i++;
				}
				// free(exec->cmd);
			}
			i = 0;
			if (exec->file != NULL)
			{
				while (exec->file[i] != NULL)
				{
					printf("REDIR %d : %s\n", i, exec->file[i]);
					// free(exec->file[i]);
					i++;
				}
				// free(exec->cmd);
			}
			j++;
			if (exec->next != NULL)
				exec = exec->next;
			else
				break ;
		}
		// free (exec);
	}
}

void	ft_all_builtin(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
{
	if (exec != NULL && exec->cmd != NULL && exec->cmd[0] != NULL)
	{
		if (ft_compare(exec->cmd[0], "pwd") == SUCCESS)
			ft_builtin_pwd(1);
		else if (ft_compare(exec->cmd[0], "cd") == SUCCESS)
			ft_builtin_cd_all(lex, env, utils);
		else if (ft_compare(exec->cmd[0], "echo") == SUCCESS)
			ft_builtin_echo_all(lex->next, env);
		else if (ft_compare(exec->cmd[0], "env") == SUCCESS)
			ft_print_list_env(env);
		else if (ft_compare(exec->cmd[0], "unset") == SUCCESS)
			ft_unset_var(lex, env);
		else if (ft_compare(exec->cmd[0], "export") == SUCCESS)
			ft_export_var(lex, env);
	}
	return ;
}

int	ft_heredoc(t_lex *lex, t_env *env)
{
	t_lex	*tmp;
	int		fd;
	char	*limiter;
	char	*input;
	char	*file;

	file = ".HEREDOC";
	tmp = lex;
	fd = 0;
	while (tmp->token != TOK_TOTO && tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->token == TOK_TOTO)
	{
		if (lex->next != NULL)
			tmp = tmp->next;
		if (tmp->next == NULL)
		{
			limiter = NULL;
			input = NULL;
		}
		else
		{
			limiter = tmp->next->str;
			input = limiter + 1;
		}
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0744);
		while (1)
		{
			input = readline(" >>");
			if (ft_strlen(input) == 0 && limiter != NULL)
				ft_organizer_heredoc(input, fd);
			else if (ft_strlen(input) != 0 && limiter == NULL)
				ft_organizer_heredoc(input, fd);
			else if (ft_strlen(input) == 0 && limiter == NULL)
				break ;
			else if (ft_compare(input, limiter) != SUCCESS)
				ft_organizer_heredoc(input, fd);
			else
				break ;
		}
	}
	else
	{
		return (1);
	}
	(void)env;
	return (0);
}
