/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:32 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:55:02 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_infile(char *str, t_fd *forces)
{
	forces->fd2 != -2 && close(forces->fd2);
	forces->fd2 = open(str, O_RDONLY);
	if (ft_check_redirection1(str) == -5)
	{
		g_gbl.ex = ft_print_error("bash", str,
				"syntax error near unexpected token `newline'\n");
		g_gbl.ex = 258;
		return (1);
	}
	else if (forces->fd2 < 0)
	{
		g_gbl.ex = ft_print_error("bash", str, "No such file or directory\n");
		return (1);
	}
	return (0);
}

int	checking(char *str)
{
	if ((str[0] == '<' && str[1] == '>') || (str[0] == '>' && str[1] == '<'))
		return (1);
	return (0);
}

int	check_hd(char *str)
{
	if ((str[0] == '<' && str[1] == '>') || (str[0] == '>' && str[1] == '<'))
		return (1);
	if (str[2] == '\n' || str[2] == '<' || str[2] == '|' || str[2] == ' '
		|| str[2] == '>' || !str[2] || str[2] == '\f' || str[2] == '\v'
		|| str[2] == '\r' || str[2] == ' ' || str[2] == '\t')
		return (1);
	return (0);
}

int	checker(t_pars **mini)
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
					&& check_hd(temp->file[i])))
				return (0);
		}
		temp = temp->next_command;
	}
	return (1);
}
