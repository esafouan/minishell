/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:00:42 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/22 13:00:44 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*help_env(char *input, int j, char *envirement)
{
	int		i;
	char	c;
	int		count;
	char	*src;

	i = j;
	c = input[j];
	while (input[j] && (input[j] == c))
		j++;
	count = j - i - 1;
	if (!count)
		count = 1;
	src = ft_substr(input, i, count);
	envirement = ft_strjoin1(envirement, src);
	free(src);
	return (envirement);
}

char	*help_envirement(char *input, int j, t_env **env, t_fd *forces)
{
	char	*envirement;
	char	*src;

	envirement = ft_calloc(1, 1);
	envirement = ft_strjoin1(envirement, ((*env)->data + j + 1));
	if (input[j] == 32)
	{
		src = space_inside_quotes(input, j, env, forces);
		envirement = ft_strjoin1(envirement, src);
		free(src);
	}
	else if (!forces->quote && input[j] == 34 && (input[j + 1] == 34 || input[j
				+ 1] == 39))
		envirement = help_env(input, j, envirement);
	else if (input[j] == '$' && input[j + 1] == 0)
		envirement = ft_strjoin1(envirement, "$");
	else if (input[j] && input[j] != '$' && input[j] != 34 && input[j] != 39)
		envirement = ft_strjoin1(envirement, input + j);
	return (envirement);
}

char	*help_envirement3(char *input, int j)
{
	char	*envirement;

	envirement = ft_calloc(1, 1);
	envirement = ft_strjoin1(envirement, "$");
	if (input[j] && input[j] != '$')
		envirement = ft_strjoin1(envirement, input + j);
	return (envirement);
}

char	*exit_status_alphanum(char *envirement, char *input, t_env **env,
		t_fd *forces)
{
	char	*tmp1;

	if (input[forces->j - 1] == '$' && input[forces->j] == '?')
	{
		tmp1 = envirement;
		envirement = help_envirement2(input, forces->j, env, forces);
		free(tmp1);
	}
	else if (input[forces->j - 1] == '$' && input[forces->j] != 32
		&& is_alpha_num(input[forces->j]) == 0 && input[forces->j] != 39
		&& input[forces->j] != 34)
	{
		tmp1 = envirement;
		envirement = help_envirement3(input, forces->j);
		free(tmp1);
	}
	return (envirement);
}

char	*help_envirement2(char *input, int j, t_env **env, t_fd *forces)
{
	char	*envirement;
	char	*tmp;

	envirement = ft_calloc(1, 1);
	tmp = ft_itoa(g_gbl.ex);
	envirement = ft_strjoin1(envirement, tmp);
	free(tmp);
	j++;
	if (input[j] && input[j] == '$' && !input[j + 1])
	{
		tmp = help_fill_variables(input + j, j, env, forces);
		envirement = ft_strjoin1(envirement, tmp);
		free(tmp);
	}
	else if (input[j] && input[j] != '$')
		envirement = ft_strjoin1(envirement, input + j);
	return (envirement);
}
