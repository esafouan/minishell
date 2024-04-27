/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:53 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/21 23:56:54 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_utils(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_pars *parsing)
{
	int	i;
	int	check;

	i = 1;
	check = 1;
	while (parsing->command[i] && ft_strncmp(parsing->command[i], "-n", 3) == 0
		&& parsing->command[i][1] == 'n')
	{
		if (ft_echo_utils(parsing->command[i]) == 0)
			break ;
		check = 0;
		i++;
	}
	while (parsing->command[i])
	{
		ft_putstr_fd(parsing->command[i], 1);
		if (parsing->command[i + 1] != 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (check == 1 || i == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}
