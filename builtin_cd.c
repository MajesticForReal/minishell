#include "minishell.h"
//permet de faire la commande "cd .." et revenir en arriere
int	ft_builtin_cd_back(char *input)
{
	int		i;
	int		size_pwd;
	char	*path_pwd;
	char	*short_pwd;

	i = 0;
	size_pwd = ft_strlen(ft_builtin_pwd(2));
	// path_pwd =  malloc(sizeof(char) * size_pwd);
	// if (path_pwd == NULL)
		// return (FAIL);
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
	(void)input;
	free(short_pwd);
	return (SUCCESS);
}
//permet de faire la commande cd san rien derrier "cd"
int	ft_builtin_cd_only(char *input, t_env *env)
{
	t_builtin *builtin;

	builtin =  malloc(sizeof(t_builtin));
	if (builtin == NULL)
		return (-1);
	while(env != NULL)
	{
		ft_compare_just_a_part(env->str, "HOME=", builtin);
		env = env->next;
	}
	if (chdir(builtin->home_str) == -1)
	{
		perror("chdir()");
		return (FAIL);
		
	}
	(void)input;
	return (SUCCESS);
}

//permet de faire la commande "cd + dossier" acceder a un dossier
int	ft_builtin_cd_dir(char *input)
{
	int	size_short_input;
	// int	size_pwd_return;
	char *complet_path;
	char *short_input;
	char *pwd_return;
	// size et size_input a revoir trop approximatif 
	// size_pwd_return = ft_strlen(ft_builtin_pwd(2) + 1);
	size_short_input = ft_strlen(input) - 1;
	// pwd_return =  malloc(sizeof(char) * size_pwd_return + 1);
	// if (pwd_return == NULL)
		// return (FAIL);
	short_input =  malloc(sizeof(char) * size_short_input);
	if (short_input == NULL)
		return (FAIL);
	short_input = ft_parsing_cd_dir(input);
	pwd_return = ft_builtin_pwd(2);
	complet_path = ft_concat(pwd_return, short_input);
	if (chdir(complet_path) == -1)
		perror("chdir()");
	free(pwd_return);
	free(short_input);
	free(complet_path);
	return (SUCCESS);
}

//permet de prendre largument apres cd "cd DOSSIER_1" 
char *ft_parsing_cd_dir(char *str)
{
	char *new_str;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_str =  malloc(sizeof(char) * ft_strlen(str) - 1);
	if (new_str == NULL)
		return (NULL);
	while(str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\f' || str[i] == '\t' || str[i] == ' ')
		i++;
	if(str[i] == 'c')
		i++;
	if(str[i] == 'd')
		i++;
	if(str[i] == ' ')
		i++;
	while(str[i] != '\0')
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return(new_str);
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

int	ft_builtin_cd_rac(char *input)
{
	if (chdir("/") == -1)
	{
		perror("chdir()");
		return (FAIL);
	}
	(void)input;
	return (SUCCESS);
}