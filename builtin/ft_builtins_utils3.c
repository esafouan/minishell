/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:37 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/27 23:35:37 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	last_child(t_fd *forces)
{
	if (forces->fd2 > 0)
	{
		close(g_gbl.l_fd[0]);
		dup2(forces->fd2, 0);
		close(forces->fd2);
	}
	else
	{
		dup2(g_gbl.l_fd[0], 0);
		close(g_gbl.l_fd[0]);
	}
	if (forces->fd1 > 0)
	{
		dup2(forces->fd1, 1);
		close(forces->fd1);
	}
	close(g_gbl.l_fd[1]);
}

void	parent_process(t_pars *temp, t_pars **mini)
{
	if (temp->id != 0)
	{
		g_gbl.l_fd = tab_pipe(mini, temp->id - 1);
		close(g_gbl.l_fd[0]);
		close(g_gbl.l_fd[1]);
	}
	g_gbl.g_status = 130;
}

void	exec_process_utils(t_pars *temp, char **env, char *path)
{
	if (temp->command[0])
		g_gbl.ex = execve(path, temp->command, env);
	if (temp->command[0] && temp->command[0][0])
	{
		ft_print_error("bash", temp->command[0], "command not found\n");
		if (g_gbl.ex != 2 && g_gbl.ex != 126)
			g_gbl.ex = 127;
		exit(g_gbl.ex);
	}
}

void	init_exec_process(t_fd *forces, t_pars **mini)
{
	forces->fd1 = -2;
	forces->fd2 = -2;
	id_cmd(mini);
	if (ft_hd2(mini, forces) == -1)
		return ;
	piping_hd(forces, mini);
	ft_hd1(mini, forces);
}

void	exp1(t_fd *forces, t_pars **mini, t_pars *temp)
{
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	if (g_gbl.g_status == 131)
	{
		g_gbl.ex = 131;
		exit(g_gbl.ex);
	}
	if (temp->id == 0)
		first_child(temp, forces);
	else if (temp->id == number_cmd(mini) - 1)
	{
		g_gbl.l_fd = tab_pipe(mini, temp->id - 1);
		last_child(forces);
	}
	else
	{
		g_gbl.l_fd = tab_pipe(mini, temp->id - 1);
		mid_child(temp, forces);
	}
}
