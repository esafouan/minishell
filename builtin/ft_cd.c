/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:51 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/23 02:35:07 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_ret(t_env *temp)
{
	free(temp);
	return (0);
}

int	cd_home(t_env **env, char *str)
{
	t_env	*temp;
	char	*pwd;
	char	*oldpwd;

	temp = *env;
	(void)str;
	if (search_home(env))
		return (ft_print_error("bash", "cd", "HOME not set\n"));
	oldpwd = getcwd(NULL, 0);
	while (temp)
	{
		if (ft_strncmp2(temp->data, "HOME=", 4) == 0)
		{
			chdir(temp->data + ft_get_home(env));
			pwd = temp->data + ft_get_home(env);
			change_it(env, "PWD=", pwd);
		}
		else if (ft_strncmp2(temp->data, "OLDPWD=", 6) == 0)
		{
			(free(temp->data), temp->data = ft_strjoin("OLDPWD=", oldpwd));
			free(oldpwd);
		}
		temp = temp->next;
	}
	return (cd_ret(temp));
}

int	ft_cd_ext(t_env **env, char *str)
{
	t_env	*temp;
	char	*pwd;
	char	*oldpwd;

	temp = *env;
	oldpwd = getcwd(NULL, 0);
	pwd = NULL;
	while (temp)
	{
		if (ft_strncmp2(temp->data, "PWD=", 3) == 0)
		{
			if (chdir(str) == -1)
			{
				free(oldpwd);
				return (ft_print_error("cd", str,
						"No such file or directory\n"));
			}
			ft_cd_ext2(temp->data, pwd);
		}
		else if (ft_strncmp2(temp->data, "OLDPWD=", 6) == 0)
			ft_cd_ext3(temp->data, oldpwd);
		temp = temp->next;
	}
	return (0);
}

int	ft_cd(t_env **env, t_pars *parsing)
{
	char	*test;

	if (parsing->command[1] == 0)
		return (cd_home(env, "HOME"));
	else if (ft_strcmp(parsing->command[1], ".") == 0)
	{
		test = getcwd(NULL, 0);
		if (!test)
			ft_print_error("cd", NULL,
				"error retrieving current directory: getcwd: cannot access parent directories: \
				No such file or directory\n");
		free(test);
		return (1);
	}
	else
		return (ft_cd_ext(env, parsing->command[1]));
	return (0);
}
