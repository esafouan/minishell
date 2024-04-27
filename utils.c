/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:31:55 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/27 01:31:57 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	for_syntx(char *input, t_inp *inp)
{
	if (input[inp->i] == '<')
		return (0);
	else if (input[inp->i] == '>' && (input[inp->i + 1] == '>' || input[inp->i
				+ 1] == '<' || input[inp->i + 1] == '|' || input[inp->i
				+ 1] == 0 || input[inp->i + 1] == 32))
		return (0);
	return (1);
}

void	elsee(char *input, t_inp *inp)
{
	inp->new[inp->k] = input[inp->i];
	inp->i++;
	inp->k++;
}

void	init_var(char *input, t_inp *inp)
{
	inp->i = 0;
	inp->k = 0;
	inp->j = ft_strlen(input) + (allocate__new_string(input) * 2) + 1;
	inp->new = malloc(sizeof(char) * inp->j);
}

void	mini_count(t_split *help, char c)
{
	while (1)
	{
		help->cpystring++;
		if (*(help->cpystring) == c || *(help->cpystring) == '\0')
		{
			help->a = 1;
			break ;
		}
	}
	help->num_word++;
}

char	*return_space(t_trim *trim)
{
	trim->tmp = malloc(sizeof(char) * 2);
	trim->tmp[0] = 32;
	trim->tmp[1] = 0;
	return (trim->tmp);
}
