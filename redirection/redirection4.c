/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:48:55 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:55:52 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ftn(t_pars *temp, int *i)
{
	if ((ft_check_redirection(temp->file[*i + 1]) == 3) || !temp->next_command)
		ft_print_error("bash", NULL,
			"syntax error near unexpected token `<<<'\n");
	else
		ft_print_error("bash", NULL,
			"syntax error near unexpected token `|'\n");
}

void	ft_hd1_nor(void)
{
	ft_print_error("bash", NULL, "syntax error near unexpected token `<<<'\n");
	g_gbl.ex = 258;
	WEXITSTATUS(g_gbl.ex);
}

void	normani(int *i, int *check)
{
	*i = -1;
	*check = 1;
}
