/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:40 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 22:32:26 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_ext2(char *str, char *pwd)
{
	char	*str1;

	pwd = getcwd(NULL, 0);
	str1 = ft_strjoin("PWD=", pwd);
	free(pwd);
	ft_strcpy(str, str1);
	free(str1);
}

void	ft_cd_ext3(char *str, char *pwd)
{
	char	*str1;

	str1 = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	ft_strcpy(str, str1);
	free(str1);
}

void	ft_pordgrass(char **env)
{
	while (wait(NULL) != -1)
		;
	free(env);
}

void	ft_pordgrass2(char **env, pid_t *pid, char *path)
{
	g_gbl.g_status = 130;
	(waitpid(*pid, &g_gbl.ex, 0));
	(free(path), free(env));
}

int	second_ret(pid_t *pid, char **env)
{
	(waitpid(*pid, &g_gbl.ex, 0), ft_pordgrass(env));
	if WIFSIGNALED ((g_gbl.ex))
		return ((g_gbl.ex + 128));
	return (WEXITSTATUS((g_gbl.ex)));
}
