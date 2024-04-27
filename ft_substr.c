/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:45:04 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/19 13:45:30 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(int count, int size)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)malloc(count * size);
	if (!p)
		return (NULL);
	while (i < count * size)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}

char	*ft_substr(char *s1, int start, int len)
{
	char	*dst;
	int		i;

	if (!s1)
		return (NULL);
	if (start >= ft_strlen(s1))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s1))
		len = ft_strlen(s1);
	i = 0;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (s1[start] && i < len && start < ft_strlen(s1))
	{
		dst[i] = s1[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	counter_single_quotes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == 39)
		{
			while (input[i] == 39)
			{
				count++;
				i++;
			}
			break ;
		}
		i++;
	}
	return (count);
}
