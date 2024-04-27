/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:22:03 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 11:22:08 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_helper(char *input, char c, t_inp *inp)
{
	inp->i++;
	if (!input[inp->i])
		inp->check = 0;
	while (input[inp->i] && input[inp->i] != c)
		inp->i++;
	if (input[inp->i] == c)
		inp->check = 1;
	else
		inp->check = 0;
}

int	syntax_error_quote(char *input, t_inp *inp)
{
	inp->check = 1;
	inp->i = 0;
	while (input[inp->i])
	{
		if (input[inp->i] == 34)
			syntax_helper(input, 34, inp);
		else if (input[inp->i] == 39)
			syntax_helper(input, 39, inp);
		inp->i++;
	}
	return (inp->check);
}

int	first_check(char *input)
{
	int	i;
	int	check;
	int	count;

	i = 0;
	count = 0;
	check = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			i++;
			while (input[i] == ' ')
			{
				count = 1;
				i++;
			}
			if (count && input[i] == '|')
				check = 1;
		}
		i++;
	}
	return (check);
}

int	syntax_help(char **string, int i, int check)
{
	if (string[i][0] == '|' && string[i + 1] == NULL)
	{
		if (string[i][1] == 0)
			check = 1;
	}
	else if (i == 0 && string[i][0] == '|' && (string[i + 1] == 0 || string[i
				+ 1][0] != '|'))
	{
		i++;
		if (string[i - 1][0] != '>')
			check = 1;
		i--;
	}
	else if (string[i][0] == '|' && string[i + 1][0] == '|')
	{
		check = 1;
		i++;
		if (string[i][0] == '|' && string[i][2] == '|')
			check = 1;
	}
	return (check);
}

int	syntax_error_pipe(char **string, char *input)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	check = first_check(input);
	while (string[i])
	{
		check = syntax_help(string, i, check);
		i++;
	}
	return (check);
}
