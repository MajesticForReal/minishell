/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:14:23 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/06 20:36:12 by anrechai         ###   ########.fr       */
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
		perror("chdir()");
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
		perror("chdir()");
		return (FAIL);
	}
	return (SUCCESS);
}

void	ft_builtin_cd_all(t_lex *lex, t_env *env, t_utils *utils)
{
	if (lex->next == NULL
		|| ft_compare(lex->next->str, "~") == SUCCESS
		|| ft_compare(lex->next->str, "~/") == SUCCESS)
		ft_builtin_cd_only(env, utils);
	else if (ft_compare(lex->next->str, "..") == SUCCESS)
		ft_builtin_cd_back();
	else if (ft_compare(lex->next->str, "/") == SUCCESS)
		ft_builtin_cd_rac();
	else
		ft_builtin_cd_dir(lex->next->str);
}

int	ft_builtin_cd_dir(char *lex_str)
{
	char	*complet_path;
	char	*pwd_return;

	pwd_return = ft_builtin_pwd(2);
	complet_path = ft_concat(pwd_return, lex_str);
	if (chdir(complet_path) == -1)
		perror("chdir()");
	free(pwd_return);
	free(complet_path);
	return (SUCCESS);
}

char	*ft_concat(char *str_1, char *str_2)
{
	char	*path;
	int		i;
	int		k;

	i = 0;
	k = 0;
	path = malloc(sizeof(char) * ft_strlen(str_1) + ft_strlen(str_2) + 2);
	if (path == NULL)
		return (NULL);
	while (str_1[i] != '\0')
	{
		path[k] = str_1[i];
		i++;
		k++;
	}
	path[k] = '/';
	k++;
	i = -1;
	while (str_2[++i] != '\0')
	{
		path[k] = str_2[i];
		k++;
	}
	path[k] = '\0';
	return (path);
}
