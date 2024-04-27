/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:58:07 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/21 23:58:08 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr_fd(char *str, char c)
{
	int	i;

	i = 1;
	if (str[0] == c)
		return (2);
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i - 1] == '+')
				return (3);
			else
				return (1);
		}
		i++;
	}
	return (0);
}
