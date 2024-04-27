/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:48 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:09:55 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_double(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		if (str[i] == '\\')
			return (i);
		i--;
	}
	return (i);
}

int	ft_cd_handler(t_env **env, char *str)
{
	t_env	*temp;
	char	*pwd;
	char	*dst;

	temp = *env;
	dst = NULL;
	while (temp)
	{
		if (ft_strncmp2(temp->data, "PWD=", 3) == 0)
		{
			ft_strlcpy(dst, temp->data, ft_cd_double(temp->data));
			temp->data = dst;
		}
		else if (ft_strncmp2(temp->data, "OLDPWD=", 6) == 0)
		{
			pwd = getcwd(NULL, 0);
			temp->data = pwd;
			free(pwd);
		}
		temp = temp->next;
	}
	return (chdir(str));
}

int	ft_get_home(t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp2(temp->data, "HOME=", 4) == 0)
			return (getvar(temp->data) + 1);
		temp = temp->next;
	}
	return (-1);
}

void	change_it(t_env **env, char *str, char *pwd)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp2(temp->data, str, 3) == 0)
		{
			free(temp->data);
			temp->data = ft_strjoin("PWD=", pwd);
		}
		temp = temp->next;
	}
}

int	search_home(t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp2(temp->data, "HOME=", 4) == 0)
		{
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
