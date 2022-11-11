/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:59:29 by klaurier          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/11 19:41:20 by klaurier         ###   ########.fr       */
=======
/*   Updated: 2022/11/11 16:12:41 by anrechai         ###   ########.fr       */
>>>>>>> dab90028671da72fa7a8909efaf280db05bac059
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_2_d_tab_test(char **strs)
{
	int	i;

	i = 0;
	if (strs[0] == NULL || strs == NULL)
		printf("strs = tableau NULL\n");
	while (strs[i] != NULL)
	{
		printf("strs[%d] = %s\n", i, strs[i]);
		i++;
	}
}

void	ft_print_3_exec(t_exec *exec)
{
	printf("\n----------afficher les tab 2 d--------------\n");
	printf("\n\ntab commande = \n");
	ft_print_2_d_tab_test(exec->cmd);
	printf("\n\n tab file = \n");
	ft_print_2_d_tab_test(exec->file);
	printf("\n\ntab path = \n");
	ft_print_2_d_tab_test(exec->path);
	if (exec->next != NULL)
	{
		exec = exec->next;
		printf("\n------------afficher les tab 2 d--exec->next------------\n");
		printf("\n\ntab commande = \n");
		ft_print_2_d_tab_test(exec->cmd);
		printf("\n\n tab file = \n");
		ft_print_2_d_tab_test(exec->file);
		printf("\n\ntab path = \n");
		ft_print_2_d_tab_test(exec->path);
	}
	if (exec->next != NULL)
	{
		exec = exec->next;
		printf("\n------------afficher les tab 2 d--exec->next->next------------\n");
		printf("\n\ntab commande = \n");
		ft_print_2_d_tab_test(exec->cmd);
		printf("\n\n tab file = \n");
		ft_print_2_d_tab_test(exec->file);
		printf("\n\ntab path = \n");
		ft_print_2_d_tab_test(exec->path);
		printf("\n\n");
	}
}

void	ft_print_1_exec(t_exec *exec)
{
	printf("\n----------afficher les tab 2 d--------------\n");
	printf("\n\ntab commande = \n");
	ft_print_2_d_tab_test(exec->cmd);
	printf("\n\n tab file = \n");
	ft_print_2_d_tab_test(exec->file);
	printf("\n\ntab path = \n");
	ft_print_2_d_tab_test(exec->path);
	printf("\n\n");
}

void	ft_print_2_exec(t_exec *exec)
{
	printf("\n----------afficher les tab 2 d--------------\n");
	printf("\n\ntab commande = \n");
	ft_print_2_d_tab_test(exec->cmd);
	printf("\n\n tab file = \n");
	ft_print_2_d_tab_test(exec->file);
	printf("\n\ntab path = \n");
	ft_print_2_d_tab_test(exec->path);
	if (exec->next != NULL)
	{
		exec = exec->next;
		printf("\n------------afficher les tab 2 d--exec->next------------\n");
		printf("\n\ntab commande = \n");
		ft_print_2_d_tab_test(exec->cmd);
		printf("\n\n tab file = \n");
		ft_print_2_d_tab_test(exec->file);
		printf("\n\ntab path = \n");
		ft_print_2_d_tab_test(exec->path);
		printf("\n\n");
	}
}

<<<<<<< HEAD
void	ft_all_builtin(t_lex *lex, t_env *env, t_utils *utils, t_env *export)
=======
void	ft_all_builtin(t_lex *lex, t_env *env, t_utils *utils, t_exec *exec)
>>>>>>> dab90028671da72fa7a8909efaf280db05bac059
{
	if (lex->str != NULL)
	{
		if (ft_compare(lex->str, "pwd") == SUCCESS)
			ft_builtin_pwd(1, exec);
		else if (ft_compare(lex->str, "cd") == SUCCESS)
			ft_builtin_cd_all(lex, env, utils, exec);
		else if (ft_compare(lex->str, "echo") == SUCCESS)
			ft_builtin_echo_all(lex, env, exec);
		else if (ft_compare(lex->str, "env") == SUCCESS)
			ft_print_list_env(env);
		else if (ft_compare(lex->str, "unset") == SUCCESS)
			ft_unset_var(lex, env);
		else if (ft_compare(lex->str, "export") == SUCCESS)
			ft_export_var(lex, env, export);
	}
}

int	ft_check_builtin(t_exec *exec)
{
	if (exec != NULL && exec->cmd != NULL && exec->cmd[0] != NULL)
	{
		if (ft_compare(exec->cmd[0], "pwd") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "cd") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "echo") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "env") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "unset") == SUCCESS)
			return (SUCCESS);
		else if (ft_compare(exec->cmd[0], "export") == SUCCESS)
			return (SUCCESS);
	}
	return (-1);
}