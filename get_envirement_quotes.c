/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envirement_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:19:10 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 11:19:13 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*help_quotes(char *input, char *envirement)
{
	int		count;
	char	*tmp1;

	count = count_qoutes(input);
	if (count != 0)
	{
		tmp1 = envirement;
		envirement = handle_qoute(input);
		free(tmp1);
	}
	return (envirement);
}

int	count_qoutes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			count++;
		i++;
	}
	return (count);
}

int	check_quote_helper(t_fd *forces, char *input, int c)
{
	while (input[forces->x] == c)
		forces->x++;
	while (input[forces->x] && input[forces->x] != c)
	{
		if (input[forces->x] == '$')
		{
			if (c == 39)
				return (1);
			else
				return (0);
		}
		forces->x++;
	}
	return (0);
}

int	check_qoute(t_fd *forces, char *input)
{
	int	check;

	check = 0;
	forces->x = 0;
	while (input[forces->x])
	{
		if (input[forces->x] == 39)
		{
			check = check_quote_helper(forces, input, 39);
			return (check);
		}
		else if (input[forces->x] == 34)
		{
			check = check_quote_helper(forces, input, 34);
			return (check);
		}
		if (input[forces->x])
			forces->x++;
	}
	return (check);
}

char	*handle_qoute(char *input)
{
	int		i;
	int		k;
	int		end;
	char	*tmp;

	i = 0;
	k = 0;
	end = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			k = i;
			i++;
			while (input[i] != 34 && input[i] != 39)
				i++;
			end = i;
			break ;
		}
		i++;
	}
	tmp = ft_strjoin1(ft_substr(input, k, end - 1), input + end + 1);
	return (tmp);
}
