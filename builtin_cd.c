/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurier <klaurier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:14:23 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 20:06:21 by klaurier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_cd_back(void)
{
	int		i;
	int		size_pwd;
	char	*path_pwd;
	char	*short_pwd;

	i = -1;
	
	size_pwd = ft_strlen(ft_builtin_pwd(2));
	path_pwd = ft_builtin_pwd(2);
	while (path_pwd[size_pwd] != '/')
		size_pwd--;
	short_pwd = malloc(sizeof(char) * size_pwd + 1);
	if (short_pwd == NULL)
		return (FAIL);
	while (++i < size_pwd)
		short_pwd[i] = path_pwd[i];
	short_pwd[i] = '\0';
	if (chdir(short_pwd) == -1)
	{
		perror(short_pwd);
		g_exstat = 1;
		free(short_pwd);
		free(path_pwd);
		return (FAIL);
	}
	free(short_pwd);
	free(path_pwd);
	return (SUCCESS);
}

int	ft_builtin_cd_only(t_env *env, t_utils *utils)
{
	while (env != NULL)
	{
		ft_compare_just_a_part(env->str, "HOME=", utils);
		env = env->next;
	}
	if (chdir(utils->home_str) == -1)
	{
		perror(utils->home_str);
		g_exstat = 1;
		return (FAIL);
	}
	return (SUCCESS);
}

void	ft_builtin_cd_all(t_lex *lex, t_env *env, t_utils *utils)
{
	if (lex->next == NULL
		|| ft_compare(lex->next->next->str, "~") == SUCCESS
		|| ft_compare(lex->next->next->str, "~/") == SUCCESS)
		ft_builtin_cd_only(env, utils);
	else if (ft_compare(lex->next->next->str, "..") == SUCCESS)
		ft_builtin_cd_back();
	else if (ft_compare(lex->next->next->str, "/") == SUCCESS)
		ft_builtin_cd_rac();
	else
		ft_builtin_cd_dir(lex->next->next->str);
}


int	ft_builtin_cd_dir(char *lex_str)
{
	char	*complet_path;
	char	*pwd_return;

	if(ft_builtin_detect_path_a_r(lex_str) == FAIL)
	{
		pwd_return = ft_builtin_pwd(2);
		printf("pwd_return = %s\n", pwd_return);
		complet_path = ft_concat(pwd_return, lex_str);
		printf("complet_path = %s\n", complet_path);
		if (chdir(complet_path) == -1)
		{
			perror(complet_path);
			g_exstat = 1;
			free(pwd_return);
			free(complet_path);
			return (FAIL);
		}
		free(pwd_return);
		free(complet_path);
		return (SUCCESS);
	}
	else
		ft_builtin_path_a(lex_str);
	return(SUCCESS);
}

int	ft_builtin_cd_rac(void)
{
	if (chdir("/") == -1)
	{
		perror("/");
		return (FAIL);
	}
	return (SUCCESS);
}