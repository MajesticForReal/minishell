/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_k.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:02:36 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/27 17:06:26 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser_k(t_lex *lex, t_env *env)
{
	t_lex	*start;
	int		i;

	start = malloc(sizeof(t_lex));
	start = lex;
	i = 0;
	while (lex != NULL)
	{
		if (lex->token == TOK_DOLL)
			ft_dollar(lex, env);
		if(lex->next != NULL)
			lex = lex->next;
		else
			break ;
		i++;
	}
	(void)i;
	(void)start;
	(void)env;
}

int	ft_compare_just_a_part_2(char *var_more)
{
	int	i;
	int	j;
	char *var_only;
	
	i = 0;
	j = -1;
	if(var_more == NULL)
		return (FAIL);
	var_only = NULL;
	while((var_more[i] <= 'z' && var_more[i] >= 'a')
	|| (var_more[i] <= 'Z' && var_more[i] >= 'A')
	|| (var_more[i] <= '9' && var_more[i] >= '0')
	|| var_more[i] == '_')
		i++;
	var_only =  malloc(sizeof(char) * i + 1);
	if (var_only == NULL)
		return (FAIL);
	while(++j < i)
		var_only[j] = var_more[j];
	var_only[j] = '\0';
	if(getenv(var_only) != NULL)
	{
		free(var_only);
		return (SUCCESS);
	}
	else
	{	
		free(var_only);
		return (FAIL);
	}
	return (SUCCESS);
}

char *ft_cut_var_more(char *var_more)
{
	int	i;
	int	j;
	char *var_only;
	
	i = 0;
	j = -1;
	var_only = NULL;
	while((var_more[i] <= 'z' && var_more[i] >= 'a')
	|| (var_more[i] <= 'Z' && var_more[i] >= 'A')
	|| (var_more[i] <= '9' && var_more[i] >= '0'))
		i++;
	var_only =  malloc(sizeof(char) * i + 1);
	if (var_only == NULL)
		return (NULL);
	while(++j < i)
		var_only[j] = var_more[j];
	var_only[j] = '\0';
	if(getenv(var_only) != NULL)
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
	while(env != NULL)
	{
		while(env->str[i] != '\0' && env->str[i] != '=')
		{
			if(env->str[i] == lex_str[i])
				i++;
			else
				break ;
		}
		if(j == i)
			return (SUCCESS);
		i = 0;
		if(env->next == NULL)
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
	
	while((lex->next->str[i] <= 'z'
	&& lex->next->str[i] >= 'a')
	|| (lex->next->str[i] <= 'Z'
	&& lex->next->str[i] >= 'A')
	|| (lex->next->str[i] <= '9'
	&& lex->next->str[i] >= '0'))
		i++;
	while(lex->next->str[i] != '\0')
	{
		j++;
		i++;
	}
	return(j);
}

int	ft_last_alpha_num(t_lex *lex)
{
	int	i;
	
	i = 0;
	while((lex->next->str[i] <= 'z'
	&& lex->next->str[i] >= 'a')
	|| (lex->next->str[i] <= 'Z'
	&& lex->next->str[i] >= 'A')
	|| (lex->next->str[i] <= '9'
	&& lex->next->str[i] >= '0'))
		i++;
	return(i);
}

void	ft_change_list_to_var(t_lex *lex)
{
	int	i;
	int	j;
	char *tmp_var;

	i = 0;
	j = ft_last_alpha_num(lex);
	i = ft_strlen(getenv(ft_cut_var_more(lex->next->str)));
	i = i + ft_char_after_var(lex);
	tmp_var = getenv(ft_cut_var_more(lex->next->str));
	lex->str =  malloc(sizeof(char) * i + 1);
	if (lex->str == NULL)
		return ;
	lex->token = TOK_WORD;
	i = 0;
	while(tmp_var[i] != '\0')
	{
		lex->str[i] = tmp_var[i];
		i++;
	}
	while(lex->next->str[j] != '\0')
	{
		lex->str[i] = lex->next->str[j];
		i++;
		j++;
	}
	lex->str[i] = '\0';
	if(lex->next->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = lex->next->next;
		return ;
	}
	else
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = NULL;
		return ;
	}
}

void	ft_cut_after_1_num(t_lex *lex)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while(lex->next->str[i] != '\0')
	{
		i++;
		j++;
	}
	i = 1;
	j = 0;
	free(lex->str);
	lex->str = malloc(sizeof(char) * j + 1);
	if (lex->str == NULL)
		return ;
	while(lex->next->str[i] != '\0')
	{
		lex->str[j] = lex->next->str[i];
		i++;
		j++;
	}
	lex->str[j] = '\0';
	lex->token = TOK_WORD;
	if(lex->next->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = lex->next->next;
		return ;
	}
	else if(lex->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = NULL;
		return ;
	}
}

int	ft_after_doll_is_num(t_lex *lex)
{
	if(lex->next->str[0] >= '0' && lex->next->str[0] <= '9' && lex->next->str[1] == '\0')
		return (SUCCESS);
	else if(lex->next->str[0] >= '0' && lex->next->str[0] <= '9' && lex->next->str[1] != '\0')
		return (SUCCESS + 1);
	else if(lex->next->str[0] == '=')
		return (SUCCESS + 2);
	return(1024);
}

void	ft_supp_2_list(t_lex *lex)
{
	free(lex->str);
	lex->str = malloc(sizeof(char) * 2);
	if(lex->str == NULL)
		return ;
	lex->str[0] = ' ';
	lex->str[1] = '\0';
	lex->token = TOK_SPACE;
	if(lex->next->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = lex->next->next;
		return ;
	}
	else
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = NULL;
		return ;
	}
}
	

void	ft_cut_after_special_char(t_lex *lex)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	free(lex->str);
	while(lex->next->str[i] != '\0')
	{
		if(lex->next->str[i] >= 'a' && lex->next->str[i] <= 'z')
			i++;
		else if(lex->next->str[i] >= 'A' && lex->next->str[i] <= 'Z')
			i++;
		else if(lex->next->str[i] >= '0' && lex->next->str[i] <= '9')
			i++;
		else if(lex->next->str[i] == '_')
			i++;
		else
			break;
	}
	k = i;
	i--;
	while(lex->next->str[++i] != '\0')
		j++;
	lex->str =  malloc(sizeof(char) * j + 1);
	if (lex->str == NULL)
		return ;
	i = 0;
	while(lex->next->str[k] != '\0')
	{
		lex->str[i] = lex->next->str[k];
		i++;
		k++;
	}
	lex->str[i] = '\0';
	if(lex->next->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = lex->next->next;
	}
	else
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = NULL;
	}
}

void	ft_change_doll_egal(t_lex *lex)
{
	int	i;

	i = 0;
	free(lex->str);
	lex->str = malloc(sizeof(char) * ft_strlen(lex->next->str) + 2);
	if(lex->str == NULL)
		return ;
	lex->str[0] = '$';
	if(lex->next != NULL)
	{
		while(lex->next->str[i] != '\0')
		{
			lex->str[i + 1] = lex->next->str[i];
			i++;
		}
		lex->str[i + 1] = '\0';
	}
	if(lex->next->next != NULL)
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = lex->next->next;
	}
	else
	{
		free(lex->next->str);
		free(lex->next);
		lex->next = NULL;
	}
}
int	ft_shearch_special_char(t_lex *lex)
{
	int	i;

	i = 0;
	while(lex->next->str[i] != '\0')
	{
		if(lex->next->str[i] >= 'a' && lex->next->str[i] <= 'z')
			i++;
		else if(lex->next->str[i] >= 'A' && lex->next->str[i] <= 'Z')
			i++;
		else if(lex->next->str[i] >= '0' && lex->next->str[i] <= '9')
			i++;
		else if(lex->next->str[i] == '_' || lex->next->str[i] == ' ')
			i++;
		else
			return(SUCCESS);
	}
	return (FAIL);
}

void	ft_dollar(t_lex *lex, t_env *env)
{
	printf("\ntest 0\n");
	if(lex->str[0] == '$' && lex->str[1] == '$')
		return ;
	if(lex->str[0] == '$' && lex->next == NULL)
		return ;
	if(ft_compare_just_a_part_2(lex->next->str) == SUCCESS)
	{
		printf("\ntest 2\n");
		ft_change_list_to_var(lex);
	}
	else if(ft_after_doll_is_num(lex) == SUCCESS)
	{
		printf("\ntest 3\n");
		ft_supp_2_list(lex);
		return ;
	}
	else if(ft_after_doll_is_num(lex) == SUCCESS + 1)
	{
		printf("\ntest 4\n");
		ft_cut_after_1_num(lex);
	}
	else if(ft_after_doll_is_num(lex) == SUCCESS + 2)
	{
		printf("\ntest 5\n");
		ft_change_doll_egal(lex);
	}
	else if(ft_shearch_var(lex->next->str, env) == FAIL && ft_shearch_special_char(lex) == FAIL)
	{
		printf("\ntest 2,5\n");
		ft_supp_2_list(lex);
	}
	else if(ft_shearch_special_char(lex) == SUCCESS)
	{
		printf("\ntest 6\n");
		ft_cut_after_special_char(lex);
	}
	(void)env;
	(void)lex;
}