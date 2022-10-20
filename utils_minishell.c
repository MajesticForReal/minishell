# include "minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
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
				printf("%s",strs[index]);
				return(1);
			}	
			printf("%s ",strs[index]);
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
		printf("%s\n", env->str);
		env = env->next;
	}
}

