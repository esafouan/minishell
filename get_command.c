/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:19:18 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 13:46:15 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_red_helper(t_help *pars, char *tempo)
{
	while (pars->cmd[pars->i][0] == '>' || pars->cmd[pars->i][0] == '<')
	{
		tempo = ft_strjoin1(tempo, " ");
		tempo = ft_strjoin1(tempo, pars->cmd[pars->i]);
		pars->cmd[pars->i][0] = 0;
		if (pars->cmd[pars->i + 1])
			pars->i++;
	}
	if (pars->cmd[pars->i][0] != '>' && pars->cmd[pars->i][0] != '<')
	{
		tempo = ft_strjoin1(tempo, " ");
		tempo = ft_strjoin1(tempo, pars->cmd[pars->i]);
		pars->cmd[pars->i][0] = 0;
	}
	return (tempo);
}

char	**get_redirection(t_help *pars)
{
	char	**out;
	char	*tempo;

	tempo = ft_calloc(1, 1);
	pars->i = 0;
	while (pars->cmd[pars->i])
	{
		if (pars->cmd[pars->i][0] == '>' || pars->cmd[pars->i][0] == '<')
		{
			tempo = get_red_helper(pars, tempo);
		}
		pars->i++;
	}
	out = ft_split(tempo);
	free(tempo);
	return (out);
}

void	get_first_cmd_help(char **string, t_help *pars)
{
	if (string[pars->i][0] != 0)
		pars->tempo = ft_strjoin1(pars->tempo, string[pars->i]);
	pars->tempo = ft_strjoin1(pars->tempo, " ");
	if (string[pars->i + 1] != NULL)
		pars->c = pars->i + 1;
	else
		pars->c = -1;
}

int	get_command(char **string, t_help *pars)
{
	pars->i = 0;
	pars->c = 0;
	if (string[0] == NULL)
		return (-1);
	pars->tempo = ft_calloc(1, 1);
	while (string[pars->i])
	{
		if (string[pars->i][0] != '|')
		{
			get_first_cmd_help(string, pars);
			if (pars->c == -1)
				break ;
		}
		else
			break ;
		pars->i++;
	}
	pars->cmd = ft_split(pars->tempo);
	pars->out = get_redirection(pars);
	pars->cmd = final_cmd(pars);
	pars->out = final_file(pars);
	free(pars->tempo);
	return (pars->c);
}

t_pars	*parser(t_pars *mini, t_help *pars, char **split)
{
	int	i;
	int	b;

	i = 0;
	b = get_command(split, pars);
	mini = ft_lstnewpars(pars);
	while (b != -1)
	{
		split = split + b + 1;
		b = get_command(split, pars);
		ft_lstadd_backpars(&mini, ft_lstnewpars(pars));
		if (b == -1)
			break ;
	}
	return (mini);
}
