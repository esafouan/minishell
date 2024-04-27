/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:28 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/27 22:22:58 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_hd1(t_pars **mini, t_fd *forces)
{
	int		i;
	int		fd;
	t_pars	*temp;

	temp = *mini;
	while (temp)
	{
		i = -1;
		while (temp->file[++i])
		{
			if ((ft_check_redirection(temp->file[i]) == 3
					&& check_hd(temp->file[i])) || checking(temp->file[i]))
			{
				(ftn(temp, &i), g_gbl.ex = 258, (*mini)->h = -3);
				return (1);
			}
			else if (ft_check_redirection(temp->file[i]) == 3)
				ft_heredoc(temp->file[i], forces, *mini, &fd);
		}
		if (g_gbl.g_status == 131)
			return (0);
		temp->h = fd;
		temp = temp->next_command;
	}
	return (0);
}

int	ft_hd2(t_pars **mini, t_fd *forces)
{
	int		i;
	t_pars	*temp;

	temp = *mini;
	while (temp)
	{
		i = -1;
		while (temp->file[++i])
		{
			if ((ft_check_redirection(temp->file[i]) == 3
					&& check_hd(temp->file[i])) || checking(temp->file[i]))
			{
				ft_print_error("bash", NULL,
					"syntax error near unexpected token `<<<'\n");
				g_gbl.ex = 258;
				forces->z = 2;
				WEXITSTATUS(g_gbl.ex);
				return (-1);
			}
		}
		temp = temp->next_command;
	}
	return (0);
}

int	ft_hd(t_pars **mini, t_fd *forces)
{
	int		i;
	t_pars	*temp;
	int		fd;

	temp = *mini;
	while (temp)
	{
		i = -1;
		while (temp->file[++i])
		{
			if ((ft_check_redirection(temp->file[i]) == 3
					&& check_hd(temp->file[i])) || checking(temp->file[i]))
			{
				ft_hd1_nor();
				forces->z = 2;
				return (-1);
			}
			else if (ft_check_redirection(temp->file[i]) == 3)
				ft_heredoc(temp->file[i], forces, *mini, &fd);
		}
		forces->fd2 = fd;
		temp->h = forces->fd2;
		temp = temp->next_command;
	}
	return (0);
}

int	ft_file(t_pars **mini, t_fd *forces)
{
	t_pars	*temp;
	int		i;
	int		check;

	temp = *mini;
	normani(&i, &check);
	while (temp->file[++i])
	{
		if (ft_check_redirection(temp->file[i]) == 3 && check)
			ft_file2(temp->fd, &check);
		else if (ft_check_redirection(temp->file[i]) == 0 && checker(mini))
		{
			if (ft_outfile(temp->file[i] + 1, forces))
				return (-1);
		}
		else if (ft_check_redirection(temp->file[i]) == 1 && checker(mini))
		{
			if (ft_append(temp->file[i] + 2, forces))
				return (-1);
		}
		else if (ft_check_redirection(temp->file[i]) == 2 && checker(mini))
			if (ft_infile(temp->file[i] + 1, forces))
				return (-1);
	}
	return (0);
}

int	ff1(t_pars **mini, t_fd *forces)
{
	t_pars	*temp;
	int		i;

	temp = *mini;
	i = -1;
	while (temp->file[++i])
	{
		if (ft_check_redirection(temp->file[i]) == 3)
			forces->fd2 = temp->h;
		else if (ft_check_redirection(temp->file[i]) == 0)
		{
			if (ft_outfile(temp->file[i] + 1, forces))
				exit(1);
		}
		else if (ft_check_redirection(temp->file[i]) == 1)
		{
			if (ft_append(temp->file[i] + 2, forces))
				exit(1);
		}
		else if (ft_check_redirection(temp->file[i]) == 2)
			if (ft_infile(temp->file[i] + 1, forces))
				exit(1);
	}
	return (0);
}
