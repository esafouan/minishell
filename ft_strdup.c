/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:10:17 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 11:15:16 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dst;

	if (!s1)
		return (NULL);
	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (0);
	while (s1[i] && i < ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
