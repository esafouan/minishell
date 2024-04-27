/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:16:29 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/27 01:16:31 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	doubleq(t_help *pars, t_env **env, t_fd *forces, t_q *q)
{
	doublq_counter(pars, forces, q);
	if (pars->split[forces->y][q->j] == '$')
	{
		q->tmp = help_fill_variables(pars->split[forces->y] + q->k, q->i, env,
				forces);
		q->exp = ft_strjoin1(q->exp, q->tmp);
		free(q->tmp);
	}
	else
	{
		while (pars->split[forces->y][q->j]
			&& pars->split[forces->y][q->j] != 34
			&& pars->split[forces->y][q->j] != '$')
			q->j++;
		q->tmp = ft_substr(pars->split[forces->y], q->i, q->j);
		q->exp = ft_strjoin1(q->exp, q->tmp);
		free(q->tmp);
	}
	skip_in_single(pars, 34, forces, q);
}

void	var_help(t_help *pars, t_fd *forces, t_q *q)
{
	q->j--;
	q->c = pars->split[forces->y][q->j];
	while (pars->split[forces->y][q->j] == q->c)
	{
		q->i++;
		q->j--;
	}
	q->src = ft_substr(pars->split[forces->y], q->j + 1, q->i);
	q->exp = ft_strjoin1(q->exp, q->src);
	free(q->src);
}

void	variabl(t_help *pars, t_env **env, t_fd *forces, t_q *q)
{
	q->i = 0;
	q->k = q->j;
	if (pars->split[forces->y][q->j - 1] == 39 || pars->split[forces->y][q->j
		- 1] == 34)
		var_help(pars, forces, q);
	q->tmp = help_fill_variables(pars->split[forces->y] + q->k, 0, env, forces);
	q->exp = ft_strjoin1(q->exp, q->tmp);
	free(q->tmp);
	q->j = q->k;
	q->j++;
	while (pars->split[forces->y][q->j] && pars->split[forces->y][q->j] != '$'
		&& pars->split[forces->y][q->j] != 39
		&& pars->split[forces->y][q->j] != 34)
		q->j++;
	q->j--;
}

void	string(t_help *pars, t_fd *forces, t_q *q)
{
	q->i = 0;
	q->k = q->j;
	if (pars->split[forces->y][q->j - 1] == 39 || pars->split[forces->y][q->j
		- 1] == 34)
		var_help(pars, forces, q);
	q->j = q->k;
	while (pars->split[forces->y][q->j] && pars->split[forces->y][q->j] != 34
		&& pars->split[forces->y][q->j] != 39
		&& pars->split[forces->y][q->j] != '$')
	{
		q->i++;
		q->j++;
	}
	q->tmp = ft_substr(pars->split[forces->y], q->k, q->i - 1);
	q->exp = ft_strjoin1(q->exp, q->tmp);
	free(q->tmp);
	if (pars->split[forces->y][q->j] != 34
		&& pars->split[forces->y][q->j] != 39)
		q->j--;
}

void	quote(t_help *pars, t_env **env, t_fd *forces)
{
	t_q	*q;

	q = malloc(sizeof(t_q));
	q->exp = ft_calloc(1, 1);
	q->j = 0;
	while (pars->split[forces->y][q->j])
	{
		if (pars->split[forces->y][q->j + 1]
			&& pars->split[forces->y][q->j] == 39)
			single(pars, env, forces, q);
		else if (pars->split[forces->y][q->j + 1]
				&& pars->split[forces->y][q->j] == 34)
			doubleq(pars, env, forces, q);
		else if (pars->split[forces->y][q->j] == '$')
			variabl(pars, env, forces, q);
		else if (pars->split[forces->y][q->j])
			string(pars, forces, q);
		q->j++;
	}
	q->tmp = pars->split[forces->y];
	pars->split[forces->y] = q->exp;
	free(q->tmp);
	free(q);
}
