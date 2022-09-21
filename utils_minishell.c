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