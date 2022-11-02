/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:58:17 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/31 19:08:11 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//permet d initialiser la s_struct env avec un malloc et en mettant a NULL next et str
t_env *ft_init_env(void)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	else
	{
		env->next = NULL;
		env->str = NULL;
	}
	return (env);
}

//permet d initaliser ET de remplir la liste chainee env en copiant le taleau envp
t_env *ft_init_fill_env(char **envp)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	else
	{
		env->next = NULL;
		env->str = NULL;
	}
	ft_fill_env(envp, env);
	(void)envp;
	return (env);
}
//permet de remplir la liste chainee env en copiant le taleau envp
void	ft_fill_env(char **envp, t_env *env)
{
	int	i;
	
	i = 0;
	env->str = malloc(sizeof(char) * (ft_strlen(envp[0]) + 1));
	while (envp[0][i])
	{
		env->str[i] = envp[0][i];
		i++;
	}
	env->str[i] = '\0';
	env->next = NULL;
	i = 0;
	while(envp[++i] != NULL)
		ft_add_back_envp(env, envp, i);
}
//permet de rajouter un maillon a la liste chainee env (a la fin)
void	ft_add_back_envp(t_env *env, char **envp, int j)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	t_env *new_env;

	new_env = ft_init_env();
	while(env->next != NULL)
		env = env->next;
	env->next = new_env;
	new_env->str = malloc(sizeof(char) * ft_strlen(envp[j]) + 1);
	if (envp[j] == NULL)
		return ;
	while(envp[j][k] != '\0')
	{
		new_env->str[l] = envp[j][k];
		k++;
		l++;
	}
	new_env->str[l] = '\0';
	(void)j;
}
