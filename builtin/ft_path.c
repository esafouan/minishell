/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:18 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/21 23:57:19 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word1(char *s1, char c)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (*s1)
	{
		if (*s1 != c && a == 0)
		{
			a = 1;
			i++;
		}
		else if (*s1 == c)
			a = 0;
		s1++;
	}
	return (i);
}

int	count_len1(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*free_split1(char **split, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

void	ft_cpysplit1(char *s, char **split, char c)
{
	int	ichar;
	int	iword;

	iword = 0;
	while (*s)
	{
		ichar = 0;
		if (*s == c)
			s++;
		else
		{
			split[iword] = (char *)malloc(sizeof(char) * count_len1(s, c) + 1);
			if (!split[iword])
				free_split1(split, count_len1(s, c));
			while (*s != c && *s)
			{
				split[iword][ichar++] = *s;
				s++;
			}
			split[iword++][ichar] = '\0';
		}
	}
	split[iword] = 0;
}

char	**ft_split2(char *s, char c)
{
	char	**split;

	split = (char **)malloc(sizeof(char *) * (count_word1(s, c) + 1));
	if (!split)
		return (NULL);
	ft_cpysplit1(s, split, c);
	return (split);
}
