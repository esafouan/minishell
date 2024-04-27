/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:19:58 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 11:20:01 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_variable(char *envirement, char *input, t_env **env,
		t_fd *forces)
{
	t_env	*tmp;
	char	*tmp1;

	tmp = *env;
	while (tmp)
	{
		forces->j = search(input, &tmp);
		envirement = expander_helper(envirement, input, &tmp, forces);
		tmp = (tmp)->next;
	}
	free(tmp);
	if (input[forces->j] == 32)
	{
		tmp1 = envirement;
		envirement = ft_strdup(input);
		free(tmp1);
	}
	return (envirement);
}

t_pars	*ft_lstnewpars(t_help *pars)
{
	t_pars	*s1;

	s1 = (t_pars *)malloc(sizeof(t_pars));
	if (!s1)
		return (NULL);
	s1->command = pars->cmd;
	s1->file = pars->out;
	s1->next_command = NULL;
	return (s1);
}

t_pars	*ft_lstlastpars(t_pars *lst)
{
	while (lst != NULL)
	{
		if (lst->next_command == NULL)
			return (lst);
		lst = lst->next_command;
	}
	return (lst);
}

void	ft_lstadd_backpars(t_pars **lst, t_pars *new)
{
	t_pars	*newlst;

	newlst = *lst;
	if (*lst)
	{
		newlst = ft_lstlastpars(newlst);
		newlst->next_command = new;
	}
	else
		*lst = new;
}
