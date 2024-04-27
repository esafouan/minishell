/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:59 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:15:45 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	getvar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (i);
		else if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_edit(t_env **env, char *str, int *n)
{
	t_env	*temp;
	int		i;

	ft_sort_list(env);
	temp = *env;
	i = -1;
	while (temp)
	{
		if (++i == *n)
		{
			if (*(temp->data + ft_parssplit(temp->data)) == '=')
			{
				if (str[getvar(str)] == '=')
					(temp->data = ft_strjoin1(temp->data, str + getvar(str)
								+ 1));
				else if (str[getvar(str)] == '+')
					(temp->data = ft_strjoin1(temp->data, str + getvar(str)
								+ 2));
			}
			else
				(temp->data = ft_strjoin1(temp->data, str + getvar(str) + 1));
			return ;
		}
		temp = temp->next;
	}
}

int	checkegal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	ft_finito_export(t_env **env, t_pars *parsing, int *x, int *i)
{
	while (parsing->command[++*i])
	{
		if (ft_check_export(parsing->command[*i]))
			ft_print_error(parsing->command[0], parsing->command[*i],
				"not a valid identifier\n");
		else
		{
			ft_sort_list(env);
			*x = ft_if_exist2(env, parsing->command[*i]);
			if (*x != -1 && checkegal(parsing->command[*i]))
			{
				ft_edit(env, parsing->command[*i], x);
			}
			else if (*x != -1)
			{
				if (*x == -2)
					continue ;
				ft_remove_if(env, parsing->command[*i]);
				add_new_env(env, parsing->command[*i]);
			}
			else
				add_new_env(env, parsing->command[*i]);
		}
	}
}

int	ft_export(t_env **env, t_pars *parsing)
{
	int	i;
	int	x;

	if (parsing->command[1] == 0)
		ft_declare(env);
	i = 0;
	ft_finito_export(env, parsing, &x, &i);
	return (0);
}
