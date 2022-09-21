#include "minishell.h"

int ft_builtin_pwd(void)
{
	char *path_dir;

    path_dir = NULL;
	
	path_dir = getcwd(path_dir, 2000);
    if (path_dir == NULL)
    {    
        free(path_dir);
        return (FAIL);
    }
    else 
        printf("%s\n", path_dir);
    free(path_dir);
    return (SUCCESS);
    (void)path_dir;
}