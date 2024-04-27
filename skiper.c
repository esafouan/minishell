/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skiper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:20:41 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 13:31:48 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_skiper(char *p, char x, t_split *help)
{
	if (p[help->a] == x)
	{
		if (p[help->a + 1] == '\0' || p[help->a + 1] == ' ' || p[help->a
				+ 1] == '\t' || p[help->a + 1] == '\n')
			help->c = 1;
		else
		{
			while (p[help->a] != ' ' && p[help->a] != '\t' && p[help->a] != '\n'
				&& p[help->a] != '\0')
				help->a++;
			help->a--;
			help->c = 1;
		}
	}
}

void	stingbefor_quote(t_split *help)
{
	help->cpystring++;
	while (*(help->cpystring) && *(help->cpystring) != 34
		&& *(help->cpystring) != 39)
		help->cpystring++;
}

int	skiper(char *p, char x, t_split *help)
{
	help->a = 0;
	help->c = 0;
	while (p[help->a])
	{
		if (p[help->a] == x)
		{
			help->a++;
			while (p[help->a] && help->c == 0)
			{
				help_skiper(p, x, help);
				help->a++;
			}
			if (help->c == 1)
				break ;
		}
	}
	return (help->a);
}

int	ft_count_cmd(char **s1, char s)
{
	int	i;
	int	j;
	int	a;

	j = 0;
	i = 0;
	a = 0;
	while (*s1)
	{
		if (*s1[0] != s && a == 0)
		{
			a = 1;
			i++;
		}
		else if (*s1[0] == s)
			a = 0;
		s1++;
	}
	return (i);
}

void	free_all(t_pars *mini, t_help *pars)
{
	t_pars	*tmp;
	int		i;

	i = 0;
	while (mini)
	{
		if (mini->command)
			free_split(mini->command);
		if (mini->file)
			free_split(mini->file);
		tmp = mini;
		mini = mini->next_command;
		free(tmp);
	}
	if (pars->split)
		free_split(pars->split);
}
