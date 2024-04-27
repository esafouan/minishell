/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:51 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/21 23:57:52 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstlast2(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*newlst;

	newlst = *lst;
	if (*lst)
	{
		newlst = ft_lstlast2(newlst);
		newlst->next = new;
	}
	else
		*lst = new;
}
