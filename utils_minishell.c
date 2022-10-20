/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:19:32 by anrechai          #+#    #+#             */
/*   Updated: 2022/10/20 17:47:02 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
		i++;
	return (i);
}

//permet de comparer l input et voir ce que lutilisateur rentre comme builtin
int	ft_compare(char *str, char *str2)
{
	int i;

	i = 0;
	while (str[i] == str2[i])
	{
		if (str[i] == '\0' && str2[i] == '\0')
			return(SUCCESS);
		i++;
	}
	return(FAIL);
}
void	ft_init_fill_str_home(char *complet_str, t_utils *utils)
{
	int	i;
	int	j;

	i = 5;
	j = 0;
	utils->home_str = malloc(sizeof(char) * ft_strlen(complet_str) - 4);
	if(utils->home_str == NULL)
		return ;
	while(complet_str[i] != '\0')
	{
		utils->home_str[j] = complet_str[i];
		i++;
		j++;
	}
	utils->home_str[j] = '\0';
}

void	ft_compare_just_a_part(char *complet_str, char *str_part, t_utils *utils)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = ft_strlen(str_part);
	while(complet_str[i] != '\0')
	{
		while(complet_str[i] == str_part[j])
		{
			if(j == k - 1)
			{
				ft_init_fill_str_home(complet_str, utils);
				return ;
			}
			j++;
			i++;
		}
		j = 0;
		i++;
	}
}

char *ft_concat2(char *str_1, char *str_2)
{
	char *new_str;
	int	i;
	int	k;

	i = 0;
	k = 0;
	new_str =  malloc(sizeof(char) * ft_strlen(str_1) + ft_strlen(str_2) + 1);
	if (new_str == NULL)
		return (NULL);
	while(str_1[i] != '\0')
	{
		new_str[k] = str_1[i];
		i++;
		k++;
	}
	// new_str[k] = '/';
	// k++;
	i = 0;
	while(str_2[i] != '\0')
	{
		new_str[k] = str_2[i];
		i++;
		k++;
	}
	new_str[k] = '\0';
	return (new_str);
}

//perme de printf un tableau 2d comme envp du mainpour voir les valeur et comparer a la liste chainee env
int	ft_print_2_d_tab(char **strs, int index)
{
	if(strs == NULL)
		return (FAIL);
	else
	{
		while(strs[index] != NULL)
		{
			if(strs[index + 1] == NULL)
			{
				ft_putstr_fd(strs[index], 1);
				return(1);
			}	
			ft_putstr_fd(strs[index], 1);
			ft_putchar_fd(' ', 1);
			index++;
		}
	}
	return (SUCCESS);
}

//permet de printf tous les maillon de la liste chainee pour verifier que la liste hainee env est la meme que le tableau 2d envp du main
void	ft_print_list_env(t_env *env)
{
	while(env != NULL)
	{
		ft_putstr_fd(env->str, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

