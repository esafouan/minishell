/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:32:24 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 13:33:24 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	allocate__new_string(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			i++;
			while (input[i] && input[i] != 34 && input[i] != 39)
				i++;
		}
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void	add_space_double_red(char *input, t_inp *inp)
{
	int	l;

	l = 2;
	inp->new[inp->k] = 32;
	inp->k++;
	while (l)
	{
		inp->new[inp->k] = input[inp->i];
		inp->k++;
		inp->i++;
		l--;
	}
	inp->new[inp->k] = 32;
	inp->k++;
}

void	skipe_inside_quotes(char *input, t_inp *inp, int c)
{
	inp->new[inp->k] = input[inp->i];
	inp->i++;
	inp->k++;
	while (input[inp->i] != c)
	{
		inp->new[inp->k] = input[inp->i];
		inp->i++;
		inp->k++;
	}
	inp->new[inp->k] = input[inp->i];
	inp->i++;
	inp->k++;
}

void	add_space_single_red(char *input, t_inp *inp)
{
	inp->new[inp->k] = 32;
	inp->k++;
	inp->new[inp->k] = input[inp->i];
	inp->k++;
	inp->i++;
	inp->new[inp->k] = 32;
	inp->k++;
}

char	*get_ready_input(char *input, t_inp *inp)
{
	init_var(input, inp);
	while (inp->k < inp->j && input[inp->i])
	{
		if (input[inp->i] == 39)
			skipe_inside_quotes(input, inp, 39);
		else if (input[inp->i] == 34)
			skipe_inside_quotes(input, inp, 34);
		else if (input[inp->i] == '>' && input[inp->i + 1] == '|')
		{
			add_space_single_red(input, inp);
			inp->i++;
		}
		else if ((input[inp->i] == '>' || input[inp->i] == '<') && (input[inp->i
					+ 1] == '>' || input[inp->i + 1] == '<'))
			add_space_double_red(input, inp);
		else if (input[inp->i] == '>' || input[inp->i] == '<'
			|| input[inp->i] == '|')
			add_space_single_red(input, inp);
		else
			elsee(input, inp);
	}
	inp->new[inp->k] = 0;
	return (inp->new);
}
