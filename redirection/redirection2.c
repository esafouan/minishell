/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:30 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/23 02:36:54 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_redirection1(char *str)
{
	if (!str)
		return (-1);
	if ((ft_strlen(str) >= 1))
		return (0);
	return (-5);
}

int	ft_check_redirection(char *str)
{
	if (!str)
		return (-1);
	if ((str[0] == '>' && str[1] != '>') && (ft_strlen(str) >= 1))
		return (0);
	else if (str[1] == '>' && (ft_strlen(str) >= 2))
		return (1);
	else if ((str[0] == '<' && str[1] != '<') && (ft_strlen(str) >= 1))
		return (2);
	else if ((str[0] == '<' && str[1] == '<') && (ft_strlen(str) >= 2))
		return (3);
	return (-5);
}

int	check_space(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (0);
		i++;
	}
	return (1);
}

int	ft_append(char *str, t_fd *forces)
{
	forces->fd1 != -2 && close(forces->fd1);
	if (check_space(str))
	{
		forces->fd1 = open(str, O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0644);
		if (forces->fd1 < 0)
		{
			g_gbl.ex = ft_print_error("bash", str,
					"No such file or directory\n");
			return (1);
		}
	}
	else if (forces->var)
	{
		g_gbl.ex = ft_print_error("bash", str, "ambiguous redirect\n");
		return (1);
	}
	return (0);
}

int	ft_outfile(char *str, t_fd *forces)
{
	forces->fd1 != -2 && close(forces->fd1);
	if (check_space(str))
	{
		forces->fd1 = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (ft_check_redirection1(str) == -5)
		{
			g_gbl.ex = ft_print_error(
					"bash", str, "syntax error near \
				   	unexpectedtoken `newline'\n");
			g_gbl.ex = 258;
			return (1);
		}
		else if ((forces->fd1) < 0)
		{
			g_gbl.ex = ft_print_error("bash", str,
					"No such file or directory\n");
			return (1);
		}
	}
	else if (forces->var)
	{
		g_gbl.ex = ft_print_error("bash", str, "ambiguous redirect\n");
		return (1);
	}
	return (0);
}
