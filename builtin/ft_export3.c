/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:17:47 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:19:52 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_declare(t_env **env)
{
	int		check;
	int		j;
	t_env	*temp;

	(ft_sort_list(env), temp = *env);
	while (temp)
	{
		(ft_putstr_fd("declare -x ", 1), check = 0);
		j = -1;
		while (temp->data[++j])
		{
			if (temp->data[j] == '"')
				j++;
			write(1, &temp->data[j], 1);
			if (temp->data[j] == '=' && check == 0)
			{
				check = 1;
				write(1, "\"", 1);
			}
			if (!temp->data[j + 1] && check == 1)
				write(1, "\"", 1);
		}
		(write(1, "\n", 1), temp = temp->next);
	}
}

int	helper_norm(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_' || c == '=')
		return (1);
	return (0);
}

int	helper_norm2(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}
