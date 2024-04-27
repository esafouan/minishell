/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:00:38 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/23 01:00:42 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntx_help(char *input, t_inp *inp)
{
	while (input[inp->i] == 32)
		inp->i++;
	if (!input[inp->i])
		return (0);
	else if (input[inp->i] == '>' || input[inp->i] == '<'
		|| input[inp->i] == '|')
		return (0);
	return (1);
}

int	syntax_error_helper(char *input, t_inp *inp)
{
	if (input[inp->i] == '<')
	{
		inp->i++;
		if (input[inp->i] == '>')
		{
			inp->i++;
			if (input[inp->i] == 32)
			{
				if (syntx_help(input, inp) == 0)
					return (0);
			}
		}
		else if (input[inp->i] == 32)
		{
			while (input[inp->i] == 32)
				inp->i++;
			if (input[inp->i] == '>' || input[inp->i] == '<'
				|| input[inp->i] == '|')
				return (0);
		}
	}
	return (1);
}

int	errorhelp(char *input, t_inp *inp)
{
	inp->i++;
	if (!input[inp->i])
		return (0);
	else if (input[inp->i] == 32)
	{
		while (input[inp->i] == 32)
			inp->i++;
		if (input[inp->i] == '>' || input[inp->i] == '<'
			|| input[inp->i] == '|')
			return (0);
	}
	else if (for_syntx(input, inp) == 0)
		return (0);
	return (1);
}

int	syntax_error_red(char *input, t_inp *inp)
{
	inp->flag = 0;
	inp->i = 0;
	while (input[inp->i])
	{
		if (input[inp->i] == 34 || input[inp->i] == 39)
			inp->flag = 1;
		else if (input[inp->i] == 34 || (input[inp->i] == 39 && inp->flag == 1))
			inp->flag = 0;
		if (input[inp->i] == '>' && inp->flag == 0)
		{
			if (errorhelp(input, inp) == 0)
				return (0);
		}
		inp->i++;
	}
	return (1);
}

int	syntax_error_red_infile(char *input, t_inp *inp)
{
	inp->i = 0;
	inp->flag = 0;
	while (input[inp->i])
	{
		if (input[inp->i] == 34 || input[inp->i] == 39)
			inp->flag = 1;
		else if (input[inp->i] == 34 || (input[inp->i] == 39 && inp->flag == 1))
			inp->flag = 0;
		else if (input[inp->i] == '<' && inp->flag == 0)
		{
			if (syntax_error_helper(input, inp) == 0)
				return (0);
			else if (input[inp->i] == '|')
				return (0);
			else if (input[inp->i] == '<' && (input[inp->i + 1] == '>'
					|| input[inp->i + 1] == '<' || input[inp->i + 1] == '|'
					|| input[inp->i + 1] == 0))
				return (0);
		}
		inp->i++;
	}
	return (1);
}
