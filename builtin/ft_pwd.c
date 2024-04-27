/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:24 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:25:01 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*path;
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)))
		printf("%s\n", buffer);
	else
	{
		path = getenv("PWD");
		if (path != NULL)
			ft_putendl_fd(path, 1);
	}
	return (0);
}
