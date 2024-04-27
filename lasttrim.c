/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lasttrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:29:53 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 13:31:00 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_count(char *tmp)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tmp[i])
	{
		while (tmp[i] == 34)
		{
			count++;
			i++;
		}
		if (count)
			break ;
		while (tmp[i] == 39)
		{
			count++;
			i++;
		}
		if (count)
			break ;
		i++;
	}
	return (count);
}

void	trim_help(t_trim *trim, char *cmd, char c)
{
	trim->i++;
	while (cmd[trim->i] && cmd[trim->i] != c)
	{
		trim->tmp[trim->j] = cmd[trim->i];
		trim->j++;
		trim->i++;
	}
	trim->i++;
}

char	*remove_midle_quotes(t_trim *trim, char *cmd)
{
	trim->j = (ft_strlen(cmd)) - (num_count(cmd) * 2);
	if (trim->j >= 0)
		trim->tmp = malloc(sizeof(char) * (trim->j + 1));
	else
		return (return_space(trim));
	if (!trim->tmp)
		return (0);
	trim->i = 0;
	trim->j = 0;
	while (cmd[trim->i])
	{
		if (cmd[trim->i] == 34)
			trim_help(trim, cmd, 34);
		else if (cmd[trim->i] == 39)
			trim_help(trim, cmd, 39);
		else
		{
			trim->tmp[trim->j] = cmd[trim->i];
			trim->j++;
			trim->i++;
		}
	}
	trim->tmp[trim->j] = 0;
	return (trim->tmp);
}

t_pars	*trim_midle_files(t_trim *trim, t_pars **mini)
{
	int		i;
	char	*fr;
	t_pars	*tmp;

	tmp = *mini;
	i = 0;
	while (*mini)
	{
		i = 0;
		while ((*mini)->file[i])
		{
			if (num_count((*mini)->file[i]) > 0)
			{
				fr = (*mini)->file[i];
				(*mini)->file[i] = remove_midle_quotes(trim, (*mini)->file[i]);
				free(fr);
			}
			i++;
		}
		*mini = (*mini)->next_command;
	}
	*mini = tmp;
	return (*mini);
}

t_pars	*trim_midle_commands(t_trim *trim, t_pars **mini)
{
	int		i;
	t_pars	*tmp;
	char	*fr;

	tmp = *mini;
	i = 0;
	while (*mini)
	{
		i = 0;
		while ((*mini)->command[i])
		{
			if (num_count((*mini)->command[i]) > 0)
			{
				fr = (*mini)->command[i];
				(*mini)->command[i] = remove_midle_quotes(trim,
						(*mini)->command[i]);
				free(fr);
			}
			i++;
		}
		*mini = (*mini)->next_command;
	}
	*mini = tmp;
	return (*mini);
}
