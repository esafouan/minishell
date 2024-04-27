/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:17:50 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 11:17:53 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	countlen(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	a3meer(char *d, long int n)
{
	if (n < 10)
		*d = n % 10 + 48;
	else
	{
		*d = (n % 10) + 48;
		a3meer(d - 1, n / 10);
	}
}

char	*ft_itoa(int n)
{
	long int	i;
	char		*dst;
	int			len;

	i = (long int)n;
	len = countlen(i);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	if (i < 0)
	{
		dst[0] = '-';
		i *= -1;
	}
	a3meer(dst + (len - 1), i);
	dst[len] = '\0';
	return (dst);
}

void	norm(t_help *pars, t_env **env, t_fd *forces)
{
	char	*tmp;

	if (check_qoute(forces, pars->split[forces->y]) == 0)
	{
		tmp = pars->split[forces->y];
		pars->split[forces->y] = help_fill_variables(pars->split[forces->y],
				forces->j, env, forces);
		free(tmp);
	}
}
