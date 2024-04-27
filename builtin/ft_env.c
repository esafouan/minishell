/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:55 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:13:42 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	convert(t_env **env, char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i = 1;
	*env = ft_lstnew2(ft_strdup(str[0]));
	while (str[i])
	{
		ft_lstadd_back(env, ft_lstnew2(ft_strdup(str[i])));
		i++;
	}
}

static int	search_path(t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp2(temp->data, "PATH=", 4) == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	ft_env(t_env **env)
{
	int		check;
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		check = 0;
		(*env)->j = -1;
		if (search_path(env))
			return (ft_print_error("bash", "env",
					"No such file or directory\n"));
		else if (!ft_strchr_fd(temp->data, '='))
			temp = temp->next;
		else
		{
			while (temp->data[++(*env)->j])
			{
				if (temp->data[(*env)->j] == '"')
					(*env)->j++;
				write(1, &temp->data[(*env)->j], 1);
			}
			(write(1, "\n", 1), temp = temp->next);
		}
	}
	return (0);
}
