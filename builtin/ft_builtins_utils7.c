/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils7.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:29:49 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:00:20 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft(t_pars *temp, t_fd *forces, t_env **envir, t_pars **mini)
{
	if (!check_builtin(temp) && (*mini)->h != -3)
	{
		(ft_exec_builtins(envir, temp, forces), exit(g_gbl.ex));
		return (1);
	}
	return (0);
}

void	ex_pr(t_env **envir, t_pars **mini, t_fd *forces, t_pars *temp)
{
	(ff1(&temp, forces), exp1(forces, mini, temp));
	ft(temp, forces, envir, mini);
}

t_pars	*ex_pr1(t_pars **mini)
{
	g_gbl.l_fd = 0;
	return (*mini);
}

t_pars	*ex_pr3(pid_t *pid, t_pars *temp, t_pars **mini, char *path)
{
	if (*pid > 0)
		parent_process(temp, mini);
	free(path);
	return (temp->next_command);
}

void	nor(t_pars **mini)
{
	(*mini)->h = 0;
	exit(g_gbl.ex);
}
