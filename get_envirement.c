/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envirement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:09:49 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 13:47:37 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*space_inside_quotes(char *input, int j, t_env **env, t_fd *forces)
{
	int		i;
	int		count;
	char	*envirement;
	char	*src;

	count = 0;
	i = j;
	envirement = ft_calloc(1, 1);
	while (input[j] && input[j] == 32)
	{
		j++;
		count++;
	}
	src = ft_substr(input, i, count);
	envirement = ft_strjoin1(envirement, src);
	free(src);
	if (input[j] == '$' && input[j + 1])
	{
		src = expander(input + j + 1, env, forces);
		envirement = ft_strjoin1(envirement, src);
		free(src);
	}
	return (envirement);
}

int	search(char *input, t_env **env)
{
	int	j;

	j = 0;
	while (input[j] && input[j] != 34 && input[j] != 39
		&& (*env)->data[j] != '=')
	{
		if ((*env)->data[j] == input[j])
			j++;
		else
			break ;
	}
	return (j);
}

int	is_alpha_num(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

char	*expander_helper(char *envirement, char *input, t_env **env,
		t_fd *forces)
{
	char	*tmp1;

	envirement = exit_status_alphanum(envirement, input, env, forces);
	if ((*env)->data[forces->j] == '=' && (input[forces->j] == '$'
			|| input[forces->j] == 0 || is_alpha_num(input[forces->j]) == 0))
	{
		tmp1 = envirement;
		envirement = help_envirement(input, forces->j, env, forces);
		free(tmp1);
	}
	else if (*envirement)
	{
		while (input[forces->j] && input[forces->j] != 34
			&& input[forces->j] != 39)
			forces->j++;
	}
	return (envirement);
}

char	*expander(char *input, t_env **env, t_fd *forces)
{
	char	*envirement;
	int		count;

	forces->i = 0;
	envirement = ft_calloc(1, sizeof(char));
	count = count_variables(input);
	envirement = first_variable(envirement, input, env, forces);
	if ((*(input + forces->j) == 34 || *(input + forces->j) == 39)
		&& count == 0)
		envirement = ft_strjoin1(envirement, input + forces->j);
	return (envirement);
}
