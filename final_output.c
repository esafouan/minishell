/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:49:06 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/18 19:51:08 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	index_of_var(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

int	num_of_cmd(t_help *pars)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (pars->cmd[i])
	{
		if (pars->cmd[i][0] != 0)
			c++;
		i++;
	}
	return (c);
}

char	*final_file_helper(t_help *pars, char *tempo, int i)
{
	if (pars->out[i] && pars->out[i][0] == '<' && pars->out[i][1] == '>')
	{
		tempo = ft_strjoin1(tempo, ">");
		i++;
	}
	while (pars->out[i] && (pars->out[i][0] == '>' || pars->out[i][0] == '<'))
	{
		tempo = ft_strjoin1(tempo, pars->out[i]);
		i++;
	}
	if (pars->out[i] && pars->out[i][0] != '<' && pars->out[i][0] != '>')
	{
		tempo = ft_strjoin1(tempo, pars->out[i]);
		tempo = ft_strjoin1(tempo, " ");
	}
	return (tempo);
}

char	**final_file(t_help *pars)
{
	int		i;
	char	*tempo;
	char	**out;

	tempo = ft_calloc(1, 1);
	i = 0;
	while (pars->out[i])
	{
		if (pars->out[i] && (pars->out[i][0] == '>' || pars->out[i][0] == '<'))
			tempo = final_file_helper(pars, tempo, i);
		if (pars->out[i])
			i++;
	}
	out = ft_split(tempo);
	free(tempo);
	free_split(pars->out);
	return (out);
}

char	**final_cmd(t_help *pars)
{
	char	**tmp;

	if (pars->cmd[0][0] == 0 && pars->cmd[1] == NULL)
	{
		free_split(pars->cmd);
		return (empty_string());
	}
	tmp = malloc(sizeof(char *) * (num_of_cmd(pars) + 1));
	if (!tmp)
		return (0);
	pars->b = 0;
	pars->j = 0;
	while (pars->cmd[pars->j])
	{
		if (pars->cmd[pars->j][0] != 0)
		{
			tmp[pars->b] = ft_strdup(pars->cmd[pars->j]);
			pars->b++;
		}
		pars->j++;
	}
	tmp[pars->b] = 0;
	free_split(pars->cmd);
	return (tmp);
}
