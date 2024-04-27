/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:16:16 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 11:16:21 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax(t_help *pars, t_inp *inp)
{
	if (syntax_error_quote(pars->input, inp) == 0
		|| syntax_error_red(pars->input, inp) == 0
		|| syntax_error_red_infile(pars->input, inp) == 0)
	{
		pars->pour = 1;
		ft_print_error("bash", NULL, "syntax error quotee\n");
		g_gbl.ex = 258;
	}
}

t_pars	*last_trim(t_pars *mini, t_help *pars, t_trim *trim)
{
	mini = parser(mini, pars, pars->split);
	mini = trim_midle_commands(trim, &mini);
	mini = trim_midle_files(trim, &mini);
	return (mini);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*p;

	p = (char *)s;
	i = 0;
	if (p[i] != (unsigned char)c)
		i++;
	while (i < ft_strlen(s) + 1)
	{
		if (p[i] == (unsigned char)c)
			return (p + i);
		else
			i++;
	}
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	lens1;
	int	i;

	i = 0;
	lens1 = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (lens1 > i && ft_strchr(set, s1[lens1]))
		lens1--;
	return (ft_substr(s1, i, lens1 - i + 1));
}
