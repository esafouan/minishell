/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:25 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/28 00:18:07 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	ft_rmv(char *curr, char *str)
{
	if (ft_strncmp2(curr, str, ft_get_var(str) - 1) == 0
		&& (str[ft_get_var(curr)] == '=' || ft_get_var(curr) == ft_strlen(str)))
		return (1);
	return (0);
}

void	ft_rem(t_env **curr, t_env *prev, t_env **env)
{
	if (prev == NULL)
		*env = (*curr)->next;
	else
		prev->next = (*curr)->next;
	(free((*curr)->data), free(*curr));
	if (prev == NULL)
		*curr = *env;
	else
		*curr = prev->next;
}

void	ft_remove_if(t_env **env, char *str)
{
	t_env	*curr;
	t_env	*prev;

	if (*env == NULL)
		return ;
	curr = *env;
	prev = NULL;
	while (curr != NULL)
	{
		if (ft_rmv(curr->data, str))
			ft_rem(&curr, prev, env);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

int	ft_unset(t_env **env, t_pars *parsing)
{
	int	i;

	i = 1;
	while (parsing->command[i])
	{
		if (ft_check_export(parsing->command[i]))
			ft_print_error(parsing->command[0], parsing->command[i],
				"not a valid identifier\n");
		else if (ft_if_exist(env, parsing->command[i]) == 1
			&& parsing->command[i][ft_strlen(parsing->command[i])
			- 1] != '=')
			ft_remove_if(env, parsing->command[i]);
		i++;
	}
	return (0);
}
