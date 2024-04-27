/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:20 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:25:44 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *cmd, t_env **envir)
{
	char	*temp;
	char	*new_path;
	char	**paths;
	int		i;

	temp = find_value("PATH", envir);
	paths = ft_split2(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmd);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(new_path, X_OK) != -1 && (cmd[0] != '.' || cmd[1] != '/')
			&& cmd[0] != '/')
		{
			free_split(paths);
			return (new_path);
		}
		free(new_path);
	}
	free_split(paths);
	return (ft_strdup(cmd));
}
