/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:42 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/28 00:15:52 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_builtins3(t_env **envir, t_pars *mini)
{
	if (ft_strcmp(mini->command[0], "echo") == 0 || ft_strcmp(mini->command[0],
			"ECHO") == 0)
		g_gbl.ex = ft_echo(mini);
	else if (ft_strcmp(mini->command[0], "cd") == 0
		|| ft_strcmp(mini->command[0], "CD") == 0)
		g_gbl.ex = ft_cd(envir, mini);
	else if (ft_strcmp(mini->command[0], "pwd") == 0
		|| ft_strcmp(mini->command[0], "PWD") == 0)
		g_gbl.ex = ft_pwd();
	else if (ft_strcmp(mini->command[0], "unset") == 0
		|| ft_strcmp(mini->command[0], "UNSET") == 0)
		g_gbl.ex = ft_unset(envir, mini);
	else if (ft_strcmp(mini->command[0], "env") == 0
		|| ft_strcmp(mini->command[0], "ENV") == 0)
		g_gbl.ex = ft_env(envir);
	else if (ft_strcmp(mini->command[0], "export") == 0
		|| ft_strcmp(mini->command[0], "EXPORT") == 0)
		g_gbl.ex = ft_export(envir, mini);
	else if (ft_strcmp(mini->command[0], "exit") == 0)
		ft_exit(mini);
}

int	ft_exec_builtins(t_env **envir, t_pars *mini, t_fd *forces)
{
	ft_exec_builtins1(mini, forces);
	if (ft_hd(&mini, forces) == -1)
		return ((g_gbl.ex));
	if (ft_file(&mini, forces) == -1)
		return (g_gbl.ex);
	signal(SIGQUIT, SIG_IGN);
	if (g_gbl.g_status == 131)
	{
		g_gbl.ex = 1;
		return (g_gbl.ex);
	}
	if (forces->z != -5)
	{
		ft_exec_builtins2(forces);
		ft_exec_builtins3(envir, mini);
	}
	forces->z = 0;
	return (g_gbl.ex);
}

int	check_builtin(t_pars *mini)
{
	if (mini->command[0])
	{
		if (ft_strcmp(mini->command[0], "echo") == 0
			|| ft_strcmp(mini->command[0], "ECHO") == 0
			|| (ft_strcmp(mini->command[0], "cd") == 0
				|| ft_strcmp(mini->command[0], "CD") == 0)
			|| (ft_strcmp(mini->command[0], "pwd") == 0
				|| ft_strcmp(mini->command[0], "PWD") == 0)
			|| (ft_strcmp(mini->command[0], "unset") == 0
				|| ft_strcmp(mini->command[0], "UNSET") == 0)
			|| (ft_strcmp(mini->command[0], "env") == 0
				|| ft_strcmp(mini->command[0], "ENV") == 0)
			|| (ft_strcmp(mini->command[0], "export") == 0
				|| ft_strcmp(mini->command[0], "EXPORT") == 0)
			|| (ft_strcmp(mini->command[0], "exit") == 0))
			return (0);
	}
	return (1);
}

int	ft_lstsize1(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**convert_tab(t_env **env, char **envir)
{
	int		i;
	t_env	*temp;

	i = ft_lstsize1(*env);
	temp = *env;
	envir = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (temp)
	{
		envir[i] = temp->data;
		i++;
		temp = temp->next;
	}
	envir[i] = NULL;
	return (envir);
}
