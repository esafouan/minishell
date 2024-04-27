/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:44 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 22:59:25 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_builtins1(t_pars *mini, t_fd *forces)
{
	forces->fd1 = -2;
	forces->fd2 = -2;
	mini->fd = -2;
	piping_hd(forces, &mini);
}

void	ft_exec_builtins2(t_fd *forces)
{
	if (forces->fd1 > 0)
		(dup2(forces->fd1, 1), close(forces->fd1));
	if (forces->fd2 > 0)
		(dup2(forces->fd2, 0), close(forces->fd2));
}

void	ft_file2(int fd, int *check)
{
	fd != -2 && close(fd);
	*check = 0;
}

void	norm_exec(char **env, char *path, pid_t *pid)
{
	g_gbl.g_status = 130;
	(waitpid(*pid, &g_gbl.ex, 0));
	(free(path), free(env));
}
