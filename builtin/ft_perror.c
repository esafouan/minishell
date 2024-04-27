/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:22 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/28 00:17:29 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *command, char *str)
{
	if (command)
	{
		ft_putstr_fd(command, 2);
		ft_putchar_fd(':', 2);
	}
	if (str && str[0])
	{
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd(':', 2);
	}
}

static void	ft_msg(int *i, int c)
{
	*i = c;
	if (c == 2)
	{
		g_gbl.ex = 2;
	}
	else if (c == 126)
		g_gbl.ex = 126;
}

int	ft_print_error(char *command, char *str, char *msg)
{
	int	i;

	i = 1;
	ft_error(command, str);
	if (msg)
	{
		if (str)
		{
			if ((str[0] == '.' && str[1] && str[1] != '/') || (str[0] == '.'
					&& str[1] == '/' && str[2]))
				(ft_msg(&i, 128), msg = "No such file or directory\n");
			else if (str[0] == '.' && !str[1])
				(ft_msg(&i, 2),
					msg = "filename argument required\n.: usage: ."
					"filename [arguments]\n");
			else if ((str[0] == '/' && !str[1]) || (str[0] == '.'
					&& str[1] == '/' && !str[2]))
				(ft_msg(&i, 126), msg = "is a directory\n");
			else if (str[0] == '/' && str[1])
				(ft_msg(&i, 127), msg = "No such file or directory\n");
		}
		ft_putchar_fd(' ', 2);
		(ft_putstr_fd(msg, 2), i = 127);
	}
	return (i);
}
