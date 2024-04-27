/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:57 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/27 23:36:30 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[++i])
		if (str[i] > '9' || str[i] < '0')
			return (0);
	return (1);
}

void	ft_exit_handler(t_pars *parsing)
{
	ft_putendl_fd("exit", 1);
	ft_print_error("exit", parsing->command[1], "numeric argument required\n");
	g_gbl.ex = 255;
	exit(g_gbl.ex);
}

void	ft_exit_finito(t_pars *parsing)
{
	if (is_num(parsing->command[1]) == 1)
	{
		ft_putendl_fd("exit", 1);
		ft_print_error("exit", parsing->command[1], "to many arguments\n");
		g_gbl.ex = ft_atoi_fd(parsing->command[1]);
		return ;
	}
	else
		ft_exit_handler(parsing);
}

void	ft_exit(t_pars *parsing)
{
	number_cmd(&parsing);
	if (parsing->next_command || parsing->id > 0)
		return ;
	if (parsing->command[1] == NULL)
	{
		ft_putendl_fd("exit", 1);
		exit(g_gbl.ex);
	}
	if (parsing->command[2] == NULL)
	{
		if (is_num(parsing->command[1]) == 1)
		{
			ft_putendl_fd("exit", 1);
			g_gbl.ex = ft_atoi_fd(parsing->command[1]);
			exit(g_gbl.ex);
		}
		else
			ft_exit_handler(parsing);
	}
	else
		ft_exit_finito(parsing);
}
