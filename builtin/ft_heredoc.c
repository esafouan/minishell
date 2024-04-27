/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:12 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/28 00:07:50 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closing_hd(t_fd *forces, t_pars **mini)
{
	int	i;
	int	j;

	i = 0;
	j = ft_number_hd(mini);
	if (forces->z != 2)
	{
		while (i < j)
		{
			close(forces->fd_hd[i][0]);
			close(forces->fd_hd[i][1]);
			free(forces->fd_hd[i]);
			i++;
		}
		free(forces->fd_hd);
	}
}

void	ft_heredoc(char *s, t_fd *forces, t_pars *mini, int *fd)
{
	char	*str;

	(pipe(forces->fd_hd[forces->i]), (forces->x = 0));
	while (1)
	{
		signal(SIGINT, handle_sigint2);
		if (g_gbl.g_status == 131)
		{
			g_gbl.ex = 1;
			forces->z = -5;
			break ;
		}
		str = readline("heredoc> ");
		if (ft_strcmp(str, s + 2) == 0)
		{
			free(str);
			break ;
		}
		if (str)
			ft_puthere(str, forces->fd_hd[forces->i][1], mini);
		free(str);
	}
	close(forces->fd_hd[forces->i][1]);
	*fd = forces->fd_hd[(forces->i)][0];
	forces->i++;
}
