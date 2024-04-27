/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:35 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 22:26:21 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	number_cmd(t_pars **mini)
{
	t_pars	*temp;
	int		i;

	temp = *mini;
	i = 0;
	while (temp)
	{
		temp->id = i;
		i++;
		temp = temp->next_command;
	}
	return (i);
}

void	id_cmd(t_pars **mini)
{
	t_pars	*temp;
	int		i;

	temp = *mini;
	i = 0;
	while (temp)
	{
		temp->id = i;
		temp = temp->next_command;
		i++;
	}
}

int	*tab_pipe(t_pars **mini, int i)
{
	t_pars	*temp;

	temp = *mini;
	while (temp)
	{
		if (temp->id == i)
			return (temp->fds);
		temp = temp->next_command;
	}
	return (NULL);
}

void	first_child(t_pars *temp, t_fd *forces)
{
	if (forces->fd2 > 0)
	{
		dup2(forces->fd2, 0);
		close(forces->fd2);
	}
	if (forces->fd1 > 0)
	{
		close(temp->fds[1]);
		dup2(forces->fd1, 1);
		close(forces->fd1);
	}
	else
	{
		dup2(temp->fds[1], 1);
		close(temp->fds[1]);
	}
	close(temp->fds[0]);
}

void	mid_child(t_pars *temp, t_fd *forces)
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
		close(temp->fds[1]);
		dup2(forces->fd1, 1);
		close(forces->fd1);
	}
	else
	{
		dup2(temp->fds[1], 1);
		close(temp->fds[1]);
	}
	close(g_gbl.l_fd[1]);
	close(temp->fds[0]);
}
