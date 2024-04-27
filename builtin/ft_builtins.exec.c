/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:46 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/28 00:14:40 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_process(t_env **envir, t_pars **mini, t_fd *forces)
{
	pid_t	pid;
	char	**env;
	t_pars	*temp;
	char	*path;

	temp = ex_pr1(mini);
	init_exec_process(forces, mini);
	if (forces->z == -5)
		return (1);
	env = convert_tab(envir, NULL);
	while (temp)
	{
		path = find_path(temp->command[0], envir);
		(temp->id != number_cmd(mini) - 1) && (pipe(temp->fds));
		pid = fork();
		if (pid == 0)
		{
			ex_pr(envir, mini, forces, temp);
			if (((*mini)->h != -3) && (!ft(temp, forces, envir, mini)))
				exec_process_utils(temp, env, path);
			nor(mini);
		}
		temp = ex_pr3(&pid, temp, mini, path);
	}
	return (second_ret(&pid, env));
}

void	exec_path_utils(t_pars **mini)
{
	if (g_gbl.ex == -1)
	{
		ft_print_error("bash", (*mini)->command[0], "command not found\n");
		if (g_gbl.ex != 2 && g_gbl.ex != 126)
			g_gbl.ex = 127;
		exit(g_gbl.ex);
	}
}

void	exec_path_utils2(t_fd *forces, t_pars **mini)
{
	forces->fd1 = -2;
	forces->fd2 = -2;
	(*mini)->fd = -2;
}

void	exec_path_utils3(t_fd *forces, t_pars **mini, char **env, char *path)
{
	if (ft_hd(mini, forces) == -1)
		return ;
	if (ft_file(mini, forces) == -1)
		return ;
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	if (g_gbl.g_status == 130 || forces->z == -5)
	{
		forces->z = 0;
		g_gbl.ex = 1;
		exit(g_gbl.ex);
	}
	if (forces->fd2 > 0)
		(dup2(forces->fd2, 0), close(forces->fd2));
	if (forces->fd1 > 0)
		(dup2(forces->fd1, 1), close(forces->fd1));
	if ((*mini)->command[0])
		g_gbl.ex = execve(path, (*mini)->command, env);
	if ((*mini)->command[0] && (*mini)->command[0][0] != 0)
		exec_path_utils(mini);
	else if (!(*mini)->file)
		g_gbl.ex = 1;
	else if ((*mini)->command[0] && (*mini)->file[0]
		&& (*mini)->command[0][0] == 0 && (*mini)->file[0][0] == 0)
		g_gbl.ex = 0;
}

int	exec_path(t_env **envir, t_pars **mini, t_fd *forces)
{
	char	**env;
	char	*path;
	pid_t	pid;

	if (ft_hd2(mini, forces) == -1)
		return (258);
	(exec_path_utils2(forces, mini), env = NULL);
	path = find_path((*mini)->command[0], envir);
	env = convert_tab(envir, env);
	(piping_hd(forces, mini), pid = fork());
	if (pid == 0)
	{
		(*mini)->fd != -2 && close((*mini)->fd);
		exec_path_utils3(forces, mini, env, path);
		exit(g_gbl.ex);
	}
	else
		norm_exec(env, path, &pid);
	if WIFSIGNALED ((g_gbl.ex))
		return ((g_gbl.ex + 128));
	return (WEXITSTATUS((g_gbl.ex)));
}
