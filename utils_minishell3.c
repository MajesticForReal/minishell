/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:59:29 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/15 16:07:03 by anrechai         ###   ########.fr       */
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

void	ft_all_builtin(t_lex *lex, t_utils *utils, t_exec *exec)
{
	if (exec != NULL && exec->cmd != NULL && exec->cmd[0] != NULL)
	{
		if (ft_compare(exec->cmd[0], "pwd") == SUCCESS)
			ft_builtin_pwd(1, exec, utils);
		else if (ft_compare(exec->cmd[0], "cd") == SUCCESS)
			ft_builtin_cd_all(lex, utils->env, utils, exec);
		else if (ft_compare(exec->cmd[0], "echo") == SUCCESS)
			ft_builtin_echo_all(lex, exec, utils);
		else if (ft_compare(exec->cmd[0], "env") == SUCCESS)
			ft_print_list_env(utils->env, exec, utils);
		else if (ft_compare(exec->cmd[0], "unset") == SUCCESS)
			ft_unset_var(lex, utils->env);
		else if (ft_compare(exec->cmd[0], "export") == SUCCESS)
			ft_export_var(lex, exec, utils);
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
