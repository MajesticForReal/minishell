/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:51:31 by anrechai          #+#    #+#             */
/*   Updated: 2022/11/05 16:32:57 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_organizer_exec(t_lex *lex, t_exec *exec, t_env *env)
{
	int		nb_pipe;
	t_lex	*first;

	nb_pipe = 1;
	first = lex;
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
		if (lex->token == TOK_SPACE)
			lex = lex->next;
		else if (lex->token == TOK_WORD)
		{
			exec->token_before = TOK_WORD;
			lex = lex->next;
			// CMD ET WORD APRES = DOC EXISTANT
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_OUT)
		{
			// IF WORD AVANT = CMD WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = DOC NO SUCH FILE OR DIRECTORY JUSAQUA LA FIN OU != TOK WORD
			// IF PAS DE WORD AVANT WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = CMD
			// ON REMPLACE LE CONTENU DU DOC
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_IN)
		{
			ft_exec_tok_in(lex, exec);
			lex = lex->next;
			while (lex != NULL && (lex->token == TOK_SPACE || lex->token == TOK_WORD))
				lex = lex->next;
			// IF PAS DE WORD AVANT WORD APRES = DOC EXISTANT ET WORD APRES CA = CMD PUIS WORD = DOC EXISTANT JUSQUA != TOK WORD
			// IF WORD AVANT WORD APRES = DOC EXISTANT JUSQUA != TOK WORD
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_FROMFROM)
		{
			// IF WORD AVANT = CMD WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = DOC NO SUCH FILE OR DIRECTORY JUSAQUA LA FIN OU != TOK WORD
			// IF PAS DE WORD AVANT WORD APRES = DOCUMENT A CREER ET TOUT LES AUTRES WORD = CMD
			// ON AJOUTE AU DOC SANS EFFACER CE QUI EXISTE DEJA DEDANS
			// LEX = LA FONCTION DU DESSUS CAR ON AVANCE
		}
		else if (lex->token == TOK_TOTO)
		{
			ft_heredoc(lex, env);
			exec->token_before = TOK_TOTO;
			lex = lex->next;
			// IF PAS DE WORD AVANT WORD APRES HERE DOC = CMD PUIS WORD APRES = DOC EXISTANT jusqua != WORD
			// IF WORD AVANT = CMD WORD APRES = DOC EXISTANT JUSQUA != WORD
			// HEREDOC DONC AVANCER APRES LE WORD LIMITER
		}
		else if (lex->token == TOK_PIPE)
		{
			ft_next_exec(exec);
			lex = lex->next;
			exec = exec->next;
			// ON VA REMPLIR LA LISTE SUIVANTE
			// ET ON PASSE LE PIPE DONC lex = lex->next
		}
	}
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
	curr->redir = NULL;
	return (curr);
}

int	ft_strlen_lst(t_lex *lex)
{
	int	i;
	int	fd;

	i = 0;
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
				close (fd);
				i++;
			};
			lex = lex->next;
		}
		else
			return (i);
	}
	return (i);
}

void	ft_exec_tok_in(t_lex *lex, t_exec *exec)
{
	int nb;
	int	i;
	int file;

	i = 0;
	if (exec->token_before == TOK_WORD)
	{
		if (lex->next->token == TOK_SPACE || lex->token == TOK_IN)
		{
			lex = lex->next;
			if (lex->token == TOK_SPACE)
			{
				lex = lex->next;
			}
		}
		if (lex->token == TOK_WORD)
		{
			nb = ft_strlen_lst(lex);
			exec->redir = malloc(sizeof(char *) * (nb + 1));
			exec->redir[nb] = NULL;
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
					exec->redir[i] = lex->str;
					i++;
					close (file);
					lex = lex->next;
				}
				else if (file == -1)
				{
					perror(lex->str);
					lex = lex->next;
					if (i == 0)
						break;
				}
				else
					break;
			}
		}
	}
	else if (exec->token_before != TOK_WORD)
	{
		// FT KEVIN
	}
	return ;
}