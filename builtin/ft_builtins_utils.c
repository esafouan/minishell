/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:33 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 22:21:35 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strc_help(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			check = i;
		i++;
	}
	return (check);
}

char	*ft_strc(char *str)
{
	int		i;
	int		check;
	char	*dst;
	int		j;

	check = ft_strc_help(str);
	if (check)
	{
		dst = malloc(ft_strlen(str));
		i = -1;
		j = 0;
		while (str[++i])
		{
			if (i != check)
			{
				dst[j] = str[i];
				j++;
			}
		}
		dst[j] = 0;
		(ft_strcpy(str, dst), free(dst));
		return (str);
	}
	return (str);
}

void	add_new_env(t_env **env, char *content)
{
	content = ft_strc(content);
	ft_lstadd_back(env, ft_lstnew2(ft_strdup(content)));
}

void	ft_sort_list(t_env **env)
{
	t_env	*temp;
	t_env	*temp1;
	char	*swap;

	temp = *env;
	while (temp->next)
	{
		temp1 = temp->next;
		while (temp1)
		{
			if (ft_strcmp(temp1->data, temp->data) < 0)
			{
				swap = temp1->data;
				temp1->data = temp->data;
				temp->data = swap;
			}
			temp1 = temp1->next;
		}
		temp = temp->next;
	}
}

char	*find_value(char *key, t_env **envir)
{
	t_env	*temp;

	temp = *envir;
	while (temp)
	{
		if (!ft_strncmp2(temp->data, key, 3))
		{
			return (temp->data + ft_strlen(key) + 1);
		}
		temp = temp->next;
	}
	return ("");
}
