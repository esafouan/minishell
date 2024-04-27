/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:23:40 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/27 01:23:47 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_odd(t_help *pars, t_fd *forces, t_q *q)
{
	q->i = q->j;
	while (pars->split[forces->y][q->j] && pars->split[forces->y][q->j] != '$')
		q->j++;
	if (pars->split[forces->y][q->j] == '$')
	{
		q->j++;
		while (pars->split[forces->y][q->j]
			&& pars->split[forces->y][q->j] != 39)
			q->j++;
		if (pars->split[forces->y][q->j] && pars->split[forces->y][q->j] != 39)
			q->j--;
		q->tmp = ft_substr(pars->split[forces->y], q->k, q->j - q->k);
		q->exp = ft_strjoin1(q->exp, q->tmp);
		free(q->tmp);
	}
	q->j = q->i;
}

void	single_even(t_help *pars, t_env **env, t_fd *forces, t_q *q)
{
	while (pars->split[forces->y][q->j] && pars->split[forces->y][q->j] != '$')
		q->j++;
	if (pars->split[forces->y][q->j] == '$')
	{
		q->src = ft_substr(pars->split[forces->y], q->k, q->j - q->k);
		q->tmp1 = help_fill_variables(pars->split[forces->y] + q->j, 0, env,
				forces);
		q->tmp = ft_strjoin1(q->src, q->tmp1);
		free(q->tmp1);
		q->exp = ft_strjoin1(q->exp, q->tmp);
		free(q->tmp);
	}
}

void	skip_in_single(t_help *pars, int c, t_fd *forces, t_q *q)
{
	q->j++;
	while (pars->split[forces->y][q->j]
		&& pars->split[forces->y][q->j] != 39
		&& pars->split[forces->y][q->j] != 34
		&& pars->split[forces->y][q->j] != '$')
		q->j++;
	if (pars->split[forces->y][q->j] == c)
		q->j = q->j + (q->j1 - 1);
	else
		q->j--;
}

void	single(t_help *pars, t_env **env, t_fd *forces, t_q *q)
{
	q->i = 0;
	q->k = q->j;
	q->j1 = 0;
	while (pars->split[forces->y][q->j] == 39)
	{
		q->i++;
		q->j1++;
		q->j++;
	}
	if (q->i % 2 == 0)
	{
		single_even(pars, env, forces, q);
		skip_in_single(pars, 39, forces, q);
	}
	else
	{
		single_odd(pars, forces, q);
		q->j++;
		while (pars->split[forces->y][q->j]
			&& pars->split[forces->y][q->j] != 39)
			q->j++;
		q->j = q->j + (q->j1 - 1);
	}
}

void	doublq_counter(t_help *pars, t_fd *forces, t_q *q)
{
	q->i = 0;
	q->k = q->j;
	q->j1 = 0;
	while (pars->split[forces->y][q->j] == 34)
	{
		q->j1++;
		q->j++;
	}
	q->j = q->k;
	while (pars->split[forces->y][q->j] && pars->split[forces->y][q->j] != '$')
	{
		q->i++;
		q->j++;
	}
}
