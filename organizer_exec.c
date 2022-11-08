/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:51:31 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/08 16:10:03 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_next_lex_to_noword(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex != NULL && lex->token != TOK_WORD)
	{
		lex = lex->next;
		i++;
	}
	return (i);
}

void	ft_bzero_exec(t_exec *exec)
{
	exec = malloc(sizeof(t_exec));
	if (exec == NULL)
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

void	ft_organizer_exec(t_lex *lex, t_exec *exec, t_env *env)
{
	int		nb_pipe;
	t_lex	*first;

	nb_pipe = 1;
	first = lex;
	ft_bzero_exec(exec);
	while (lex != NULL)
	{
		if (lex->token == TOK_PIPE)
			nb_pipe++;
		lex = lex->next;
	}
	lex = first;
	exec->token_before = 0;
	while (lex != NULL)
	{
		if (lex->token == TOK_SPACE && lex->next != NULL)
			lex = lex->next;
		else if (lex->token == TOK_WORD)
		{
			printf("TEST 1\n");
			ft_init_fill_t_exec(lex, exec, env);
			while (lex->next != NULL && (lex->token == TOK_WORD
					|| lex->token == TOK_SPACE))
				if (lex->next != NULL)
					lex = lex->next;
			if (lex == NULL || lex->next == NULL)
				return ;
		}
		else if (lex->token == TOK_OUT)
		{
			printf("TEST 2\n");
			if (exec->token_before == TOK_WORD)
			{
				ft_init_fill_redir_out(lex, exec);
				lex = lex->next;
				while (lex->next != NULL && (lex->token == TOK_WORD
						|| lex->token == TOK_SPACE))
					lex = lex->next;
			}
			else if (exec->token_before != TOK_WORD)
			{
				ft_init_one_fill_redir_out(lex, exec);
				while (lex != NULL && lex->token != TOK_WORD)
					lex = lex->next;
				lex = lex->next;
			}
			if (lex == NULL || lex->next == NULL)
				return ;
			exec->token_before = TOK_WORD;
			lex = lex->next;
		}
		else if (lex->token == TOK_IN)
		{
			printf("TEST 3\n");
			ft_exec_tok_in(lex, exec);
			lex = lex->next;
			if (exec->token_before == TOK_WORD)
			{
				while (lex != NULL && (lex->token == TOK_SPACE
						|| lex->token == TOK_WORD))
					lex = lex->next;
			}
			else if (exec->token_before != TOK_WORD)
			{
				if (lex->token == TOK_SPACE)
					lex = lex->next;
				if (lex->token == TOK_WORD)
					lex = lex->next;
			}
		}
		else if (lex->token == TOK_FROMFROM)
		{
			printf("TEST 4\n");
			if (exec->token_before == TOK_WORD)
			{
				ft_init_fill_redir_out(lex, exec);
				lex = lex->next;
				while (lex->next != NULL && (lex->token == TOK_WORD
						|| lex->token == TOK_SPACE))
					lex = lex->next;
			}
			else if (exec->token_before != TOK_WORD)
			{
				ft_init_one_fill_redir_out(lex, exec);
				while (lex != NULL && lex->token != TOK_WORD)
					if (lex->next != NULL)
						lex = lex->next;
				lex = lex->next;
			}
			if (lex == NULL || lex->next == NULL)
				return ;
		}
		else if (lex->token == TOK_TOTO)
		{
			printf("TEST 5\n");
			ft_heredoc(lex, env);
			exec->token_before = TOK_TOTO;
			lex = lex->next;
		}
		else if (lex->token == TOK_PIPE)
		{
			printf("TEST 6\n");
			ft_next_exec(exec);
			lex = lex->next;
			exec = exec->next;
			// ON VA REMPLIR LA LISTE SUIVANTE
			// ET ON PASSE LE PIPE DONC lex = lex->next
		}
		// lex = lex->next;
	}
	printf("OUT\n");
	(void)exec;
	(void)env;
}

void	ft_init_fill_cmd(t_lex *lex, t_exec *exec)
{
	int	i;
	int	j;
	int	k;
	int	fd;

	fd = 0;
	k = 0;
	i = 0;
	j = 0;
	exec->cmd = malloc(sizeof(char *) * (exec->nb_option + 2));
	exec->cmd[exec->nb_option + 1] = NULL;
	if (exec->cmd == NULL)
		return ;
	exec->cmd[0] = lex->str;
	i = 1;
	if (lex->next != NULL)
		lex = lex->next;
	else
		return ;
	while (lex != NULL && (lex->token == TOK_WORD || lex->token == TOK_SPACE))
	{
		if (k >= exec->nb_option)
		{
			exec->cmd[i] = NULL;
			return ;
		}
		if (lex->token == TOK_WORD && lex->str[0] != '-')
		{
			fd = open(lex->str, O_RDONLY);
			if (fd != -1)
				close(fd);
			else
				perror(lex->str);
		}
		if (lex->token == TOK_WORD)
		{
			exec->cmd[i] = lex->str;
			k++;
			i++;
			if (k == exec->nb_option)
			{
				exec->cmd[i] = NULL;
				return ;
			}
		}
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	exec->cmd[i] = NULL;
	(void)j;
}

void	ft_print_2_d_tab_test(char **strs)
{
	int	i;

	i = 0;
	if (strs[0] == NULL || strs == NULL)
		printf("strs = tableau NULL\n");
	while (strs[i] != NULL)
	{
		printf("strs[%d] = %s\n", i, strs[i]);
		i++;
	}
}

void	ft_init_fill_tab_path(t_lex *lex, t_exec *exec, t_env *env)
{
	char	*path;

	path = getenv("PATH");
	exec->path = ft_split(path, ':');
	(void)lex;
	(void)env;
	(void)exec;
}

void	ft_count_option(t_lex *lex, t_exec *exec)
{
	exec->nb_option = 0;
	if (lex->next != NULL)
		lex = lex->next;
	while (lex != NULL && lex != NULL && (lex->token == TOK_WORD
			|| lex->token == TOK_SPACE))
	{
		if (lex->token == TOK_WORD)
		{
			if (lex->str[0] == '-' && lex->str[1] != '\0' && lex->str[1] != ' ')
				exec->nb_option++;
			else
				return ;
		}
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	return ;
}

int	ft_count_fd(t_lex *lex, t_exec *exec)
{
	int	i;

	i = 0;
	while (lex->next != NULL && lex != NULL && (lex->token == TOK_WORD
			|| lex->token == TOK_SPACE))
	{
		if (lex->str[0] != '-' && lex->token == TOK_WORD)
			i++;
		lex = lex->next;
	}
	(void)exec;
	return (i);
}

void	ft_init_one_fill_redir_out(t_lex *lex, t_exec *exec)
{
	if (lex->next != NULL && lex->next->token == TOK_SPACE)
	{
		lex = lex->next;
		if (lex->next != NULL)
			lex = lex->next;
		else
			return ;
	}
	else if (lex->next != NULL)
		lex = lex->next;
	if (lex->token == TOK_WORD)
	{
		exec->file = malloc(sizeof(char *) * 2);
		exec->file[0] = lex->str;
		exec->file[1] = NULL;
	}
}

void	ft_init_fill_redir_out(t_lex *lex, t_exec *exec)
{
	int	fd;

	fd = 0;
	if (lex->next != NULL)
		lex = lex->next;
	else
		return ;
	if (lex->next != NULL && lex->token == TOK_SPACE)
		lex = lex->next;
	if (lex->token == TOK_WORD)
	{
		exec->file = malloc(sizeof(char *) * 2);
		exec->file[0] = lex->str;
		exec->file[1] = NULL;
		if (lex->next != NULL)
			lex = lex->next;
		else
			return ;
	}
	while (lex != NULL && (lex->token == TOK_SPACE || lex->token == TOK_WORD))
	{
		if (lex->token == TOK_WORD)
		{
			fd = open(lex->str, O_RDONLY);
			if (fd != -1)
				close(fd);
			else
				perror(lex->str);
		}
		if (lex->next != NULL)
			lex = lex->next;
		else
			return ;
	}
}

void	ft_init_one_fill_redir(t_lex *lex, t_exec *exec)
{
	int	fd;

	fd = -1;
	if (lex->next != NULL && lex->next->token == TOK_SPACE)
	{
		lex = lex->next;
		if (lex->next != NULL)
			lex = lex->next;
		else
			return ;
	}
	else if (lex->next != NULL)
		lex = lex->next;
	exec->file = malloc(sizeof(char *) * 2);
	if (exec->file == NULL)
		return ;
	if (lex->token == TOK_WORD)
	{
		fd = open(lex->str, O_RDONLY);
		if (fd != -1)
			exec->file[0] = lex->str;
		else
		{
			perror(lex->str);
			close(fd);
			return ;
		}
	}
	exec->file[1] = NULL;
}

void	ft_init_fill_redir(t_lex *lex, t_exec *exec)
{
	int	fd;

	fd = -1;
	if (lex->next != NULL)
		lex = lex->next;
	else
		return ;
	while (lex != NULL && (lex->token == TOK_SPACE || lex->token == TOK_WORD))
	{
		if (lex->token == TOK_WORD && lex->str[0] != '-')
		{
			fd = open(lex->str, O_RDONLY);
			if (fd != -1)
				close(fd);
			else
				perror(lex->str);
		}
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	(void)fd;
	(void)exec;
}

void	ft_init_fill_t_exec(t_lex *lex, t_exec *exec, t_env *env)
{
	exec->token_before = TOK_WORD;
	exec->cmd_size = ft_strlen(lex->str);
	ft_count_option(lex, exec);
	ft_init_fill_cmd(lex, exec);
	ft_init_fill_tab_path(lex, exec, env);
	ft_init_fill_redir(lex, exec);
	// ft_print_2_d_tab_test(exec->path);
	// ft_print_2_d_tab_test(exec->cmd);
	// ft_print_2_d_tab_test(exec->file);
	(void)env;
	(void)lex;
	(void)exec;
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
	curr->file = NULL;
	return (curr);
}

int	ft_strlen_lst(t_lex *lex)
{
	int	i;
	int	fd;

	i = 0;
	lex = lex->next;
	while (lex != NULL && (lex->token == TOK_WORD || lex->token == TOK_SPACE))
	{
		if (lex->token == TOK_SPACE)
		{
			lex = lex->next;
		}
		else if (lex->token == TOK_WORD)
		{
			if ((fd = open(lex->str, O_RDONLY)) != -1)
			{
				close(fd);
				i++;
			};
			lex = lex->next;
		}
		else
			return (i);
	}
	return (i);
}

void	ft_exec_exist(t_exec *exec, t_lex *lex, int token)
{
	int		i;
	int		file;
	int		nb;
	char	**tmp;
	char	**new;

	i = 0;
	while (exec->file[i] != NULL)
	{
		i++;
	}
	nb = ft_strlen_lst(lex) + 1;
	new = malloc(sizeof(char *) * (nb + i + 1));
	new[nb + i] = NULL;
	i = 0;
	while (exec->file[i] != NULL)
	{
		new[i] = exec->file[i];
		i++;
	}
	if (lex->token == token)
	{
		new[i] = lex->str;
		i++;
		lex = lex->next;
	}
	while (lex != NULL && (lex->token == TOK_SPACE || lex->token == TOK_WORD))
	{
		if (lex->token == TOK_WORD)
		{
			file = open(lex->str, O_RDONLY);
			if (file != -1)
			{
				new[i] = lex->str;
				i++;
				close(file);
			}
			else if (file == -1)
			{
				perror(lex->str);
				if (i == 0)
					break ;
			}
		}
		lex = lex->next;
	}
	tmp = exec->file;
	exec->file = new;
	free(tmp);
}

void	ft_exec_tok_in(t_lex *lex, t_exec *exec)
{
	int	nb;
	int	i;
	int	file;

	i = 1;
	if (exec->token_before == TOK_WORD)
	{
		if (lex->next->token == TOK_SPACE || lex->token == TOK_IN)
		{
			if (exec->file != NULL)
				ft_exec_exist(exec, lex, TOK_IN);
			else
			{
				nb = ft_strlen_lst(lex) + 1;
				exec->file = malloc(sizeof(char *) * (nb + 1));
				exec->file[nb] = NULL;
				exec->file[0] = lex->str;
				if (lex->next->token == TOK_SPACE || lex->token == TOK_IN)
				{
					lex = lex->next;
					if (lex->token == TOK_SPACE)
					{
						lex = lex->next;
					}
				}
				while (lex != NULL && (lex->token == TOK_WORD
						|| lex->token == TOK_SPACE))
				{
					if (lex->token == TOK_SPACE)
					{
						lex = lex->next;
					}
					if (lex->token != TOK_WORD)
						return ;
					file = open(lex->str, O_RDONLY);
					if (file != -1)
					{
						exec->file[i] = lex->str;
						i++;
						close(file);
						lex = lex->next;
					}
					else if (file == -1)
					{
						perror(lex->str);
						lex = lex->next;
						if (i == 0)
							break ;
					}
					else
						break ;
				}
			}
		}
	}
	else if (exec->token_before != TOK_WORD)
	{
		printf("PAS ICI\n");
		lex = lex->next;
		if (lex->token == TOK_SPACE)
		{
			lex = lex->next;
		}
		if (lex->token == TOK_WORD)
		{
			file = open(lex->str, O_RDONLY);
			if (file != -1)
			{
				exec->file = malloc(sizeof(char *) * (1 + 1));
				exec->file[1] = NULL;
				exec->file[0] = lex->str;
				close(file);
				lex = lex->next;
			}
			else if (file == -1)
			{
				perror(lex->str);
				lex = lex->next;
			}
		}
	}
	return ;
}
