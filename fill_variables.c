/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:42:55 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/18 19:48:46 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*help_fill_variables(char *split, int j, t_env **env, t_fd *forces)
{
	char	*tmp;
	char	*tmp1;

	j++;
	if (j == 1)
		split = expander(split + j, env, forces);
	else if (j > 1)
	{
		if (split[j] == 32)
			tmp = ft_substr(split, 0, j);
		else
			tmp = ft_substr(split, 0, j - 1);
		tmp1 = expander(split + j, env, forces);
		split = ft_strjoin(tmp, tmp1);
		free(tmp1);
		free(tmp);
	}
	return (split);
}

char	*help_hindle_quote(char *split, t_env **env, t_fd *forces)
{
	int		i;
	char	*tmp;

	tmp = split;
	i = 0;
	split = ft_strtrim(split, "\'");
	free(tmp);
	while (split[i])
	{
		if (split[i] == '$')
		{
			tmp = split;
			split = help_fill_variables(split, i, env, forces);
			free(tmp);
			break ;
		}
		i++;
	}
	return (split);
}

int	count_variables_inside_quotes(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && (s[i + 1] && s[i + 1] != 34 && s[i
					+ 1] != 39))
			count++;
		i++;
	}
	return (count);
}

void	norm_fill_variables(t_help *pars, t_env **env, t_fd *forces)
{
	forces->envfr = env;
	if (count_variables_inside_quotes(pars->split[forces->y]) <= 1
		&& count_variables(pars->split[forces->y]) <= 1)
	{
		forces->quote = 1;
		if (check_qoute(forces, pars->split[forces->y]) == 1
			&& counter_single_quotes(pars->split[forces->y]) % 2 == 0)
			pars->split[forces->y] = help_hindle_quote(pars->split[forces->y],
					env, forces);
		else if (forces->y == 0)
			norm(pars, env, forces);
		else if (forces->y && pars->split[forces->y - 1][1] != '<')
			norm(pars, env, forces);
	}
	else
	{
		forces->quote = 0;
		quote(pars, env, forces);
	}
}

void	fill_variables(t_help *pars, t_env **env, t_fd *forces)
{
	forces->y = 0;
	while (pars->split[forces->y] != NULL)
	{
		forces->j = 0;
		while (pars->split[forces->y][forces->j])
		{
			if (pars->split[forces->y][forces->j] == '$'
				&& pars->split[forces->y][forces->j + 1] != 0)
			{
				norm_fill_variables(pars, env, forces);
				break ;
			}
			forces->j++;
		}
		forces->y++;
	}
}
