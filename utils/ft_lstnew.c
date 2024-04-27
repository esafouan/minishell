/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:55 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 01:49:12 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew2(char *content)
{
	t_env	*s1;

	s1 = (t_env *)malloc(sizeof(t_env));
	if (!s1)
		return (NULL);
	s1->data = content;
	s1->next = NULL;
	return (s1);
}
