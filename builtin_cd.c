#include "minishell.h"
//permet de faire la commande "cd .." et revenir en arriere
int	ft_builtin_cd_back(void)
{
	int		i;
	int		size_pwd;
	char	*path_pwd;
	char	*short_pwd;

	i = 0;
	size_pwd = ft_strlen(ft_builtin_pwd(2));
	path_pwd = ft_builtin_pwd(2);
	while(path_pwd[size_pwd] != '/')
		size_pwd--;
	short_pwd =  malloc(sizeof(char) * size_pwd + 1);
	if (short_pwd == NULL)
		return (FAIL);
	while(i < size_pwd)
	{
		short_pwd[i] = path_pwd[i];
		i++;
	}
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
//permet de faire la commande cd san rien derrier "cd"
int	ft_builtin_cd_only(t_env *env)
{
	t_utils *utils;

	utils = malloc(sizeof(t_utils));
	if (utils == NULL)
		return (-1);
	while(env != NULL)
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

//permet de faire la commande "cd + dossier" acceder a un dossier
void	ft_builtin_cd_all(t_lex *lex, t_env *env)
{
	if(lex->next == NULL
		|| ft_compare(lex->next->str, "~") == SUCCESS
		|| ft_compare(lex->next->str, "~/") == SUCCESS)
		ft_builtin_cd_only(env);
	else if(ft_compare(lex->next->str, "..") == SUCCESS)
		ft_builtin_cd_back();
	else if(ft_compare(lex->next->str, "/") == SUCCESS)
		ft_builtin_cd_rac();
	else
		ft_builtin_cd_dir(lex->next->str);

}

int	ft_builtin_cd_dir(char *lex_str)
{
	char *complet_path;
	char *pwd_return;

	pwd_return = ft_builtin_pwd(2);
	complet_path = ft_concat(pwd_return, lex_str);
	if (chdir(complet_path) == -1)
		perror("chdir()");
	free(pwd_return);
	free(complet_path);
	return (SUCCESS);
}

//pemet de concatener largument au path actuel "cd DOSSIER_1"
//DOSSIER_1 est copier et rajouter au path avec un "/" en plus/mnt/nfs/homes/klaurier/Desktop/C/minishell/DOSSIER_1
char *ft_concat(char *str_1, char *str_2)
{
	char *path;
	int	i;
	int	k;

	i = 0;
	k = 0;
	path =  malloc(sizeof(char) * ft_strlen(str_1) + ft_strlen(str_2) + 2);
	if (path == NULL)
		return (NULL);
	while(str_1[i] != '\0')
	{
		path[k] = str_1[i];
		i++;
		k++;
	}
	path[k] = '/';
	k++;
	i = 0;
	while(str_2[i] != '\0')
	{
		path[k] = str_2[i];
		i++;
		k++;
	}
	path[k] = '\0';
	return (path);
}

int	ft_builtin_cd_rac(void)
{
	if (chdir("/") == -1)
	{
		perror("chdir()");
		return (FAIL);
	}
	return (SUCCESS);
}