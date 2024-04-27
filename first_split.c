/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:52:12 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/26 14:58:37 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(t_split *help)
{
	help->a = 0;
	help->num_word = 0;
	while (*(help->cpystring))
	{
		if (help->a == 1 && (*(help->cpystring) == 34
				|| *(help->cpystring) == 39))
			stingbefor_quote(help);
		else if (*(help->cpystring) == 34)
			mini_count(help, 34);
		else if (*(help->cpystring) == 39)
			mini_count(help, 39);
		else if (help->a == 0 && *(help->cpystring) != ' '
			&& *(help->cpystring) != '\t' && *(help->cpystring) != '\n')
		{
			help->a = 1;
			help->num_word++;
		}
		else if (*(help->cpystring) == ' ' || *(help->cpystring) == '\t'
			|| *(help->cpystring) == '\n')
			help->a = 0;
		help->cpystring++;
	}
	return (help->num_word);
}

char	*fill_word(char *p, t_split *help)
{
	char	*word;

	help->count = 0;
	if (p[help->count] != 34 && p[help->count] != 39)
	{
		while (p[help->count] && p[help->count] != ' ' && p[help->count] != '\t'
			&& p[help->count] != '\n')
		{
			if (p[help->count] == 39 || p[help->count] == 34)
			{
				help->count += skiper(p + help->count, p[help->count], help);
				help->count--;
			}
			help->count++;
		}
	}
	else if (p[help->count] && p[help->count] == 34)
		help->count = skiper(p, 34, help);
	else if (p[help->count] && p[help->count] == 39)
		help->count = skiper(p, 39, help);
	word = malloc(sizeof(char) * (help->count + 1));
	word = ft_strlcpy1(word, p, help->count);
	return (word);
}

char	**empty_string(void)
{
	char	**split;

	split = malloc(sizeof(char *) * 2);
	if (!split)
		return (0);
	split[0] = ft_calloc(1, 1);
	split[1] = 0;
	return (split);
}

void	init_struct_split(t_split	*help, char *dst)
{
	help->cpystring = dst;
	help->b = count_word(help);
}

char	**ft_split(char *dst)
{
	int		i;
	char	**split;
	t_split	*help;

	i = 0;
	while (*dst == 32 || *dst == '\t')
		dst++;
	if (*dst == '\0')
		return (empty_string());
	help = malloc(sizeof(t_split));
	init_struct_split(help, dst);
	split = malloc((sizeof(char *) * (help->b + 1)));
	if (!split)
		return (0);
	while (*dst && i < help->b)
	{
		while (*dst == ' ' || *dst == '\t' || *dst == '\n')
			dst++;
		split[i] = fill_word(dst, help);
		i++;
		dst += help->count;
	}
	split[i] = 0;
	free(help);
	return (split);
}
