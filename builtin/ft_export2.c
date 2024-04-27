/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:17:22 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:16:49 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_export(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (helper_norm2(str[i]))
		i++;
	else
		return (1);
	while (str[i])
	{
		if (helper_norm(str[i]))
		{
			if (str[i] == '=')
				break ;
			i++;
		}
		else if (str[i] == '+' && (str[i + 1] == '=' || str[i - 1] == '='
				|| check))
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_parssplit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || str[i] == '+')
			return (i);
		i++;
	}
	return (i);
}

int	ft_if_exist(t_env **env, char *str)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->data, str, ft_strlen(str)) == 0
			&& ft_parssplit(str) == ft_parssplit(temp->data))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	ft_if_exist2(t_env **env, char *str)
{
	t_env	*temp;
	int		i;

	temp = *env;
	i = 0;
	while (temp)
	{
		if (ft_strncmp2(temp->data, str, getvar(str) - 1) == 0
			&& ft_parssplit(str) == ft_parssplit(temp->data))
		{
			if (ft_get_var(temp->data) == ft_strlen(str))
				return (-2);
			return (i);
		}
		temp = temp->next;
		i++;
	}
	return (-1);
}
