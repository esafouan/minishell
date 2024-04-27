/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:15:28 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 11:15:34 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_check(char *input)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (input && input[i])
	{
		if (input[i] == '$')
		{
			check = 1;
			break ;
		}
		i++;
	}
	return (check);
}

int	count_variables(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	lexer_expander_helper(t_env **env, t_fd *forces, t_help *pars,
		t_inp *inp)
{
	char	*tmp;

	syntax(pars, inp);
	if (pars->pour == 0)
	{
		tmp = pars->input;
		pars->input = get_ready_input(pars->input, inp);
		free(tmp);
		pars->split = ft_split(pars->input);
		fill_variables(pars, env, forces);
		(*env)->cmd_count = ft_count_cmd(pars->split, '|');
		if (syntax_error_pipe(pars->split, tmp) == 1)
		{
			pars->pour = 1;
			ft_print_error("bash", NULL,
				"syntax error near unexpected token `newline\n");
			free_split(pars->split);
			g_gbl.ex = 258;
		}
	}
}

void	lexer_expander(t_env **env, t_fd *forces, t_help *pars)
{
	t_inp			*inp;
	struct termios	term;
	struct termios	oldterm;

	inp = malloc(sizeof(t_inp));
	pars->pour = 0;
	tcgetattr(0, &term);
	oldterm = term;
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	pars->input = readline("minishell : ");
	forces->var = var_check(pars->input);
	tcsetattr(0, TCSANOW, &oldterm);
	if (!pars->input)
		exit(0);
	add_history(pars->input);
	lexer_expander_helper(env, forces, pars, inp);
	free(inp);
	free(pars->input);
}

char	*ft_strlcpy1(char *dst, char *src, int dstsize)
{
	int	i;
	int	a;

	a = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}
