/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_exp2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:04 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:23:04 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_here(char *str, int fin, int fd, t_pars *mini)
{
	int		i;
	char	*dst;

	fin = (size_t)fin;
	dst = malloc(sizeof(char) * fin + 1);
	i = 0;
	while (i < fin)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = 0;
	dst = fill_exp(dst, mini->env);
	if (dst[0])
	{
		i = -1;
		while (dst[++i])
			write(fd, &dst[i], 1);
	}
	free(dst);
}

void	ft_my_putstr(char *str, int fin, int fd)
{
	int	i;

	i = 0;
	while (i < fin)
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

int	is_this(char c)
{
	char	*str;
	int		i;

	str = "-*/\"'+.,;#?<|>:";
	i = 0;
	while (str[i])
	{
		if (c == str[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	norm_put(int *fin, int *start, int *check)
{
	*start = 0;
	*fin = 0;
	*check = 1;
}

void	ft_puthere(char *str, int fd, t_pars *mini)
{
	int	i;
	int	start;
	int	fin;
	int	check;

	i = -1;
	check = 1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && check)
		{
			start = i;
			check = 0;
		}
		else if (((str[i + 1] == ' ' || str[i + 1] == 0 || str[i + 1] == '$')
				|| is_this(str[i + 1])) && !check)
		{
			fin = i + 1;
			ft_putstr_here(str + start, fin - start, fd, mini);
			norm_put(&fin, &start, &check);
		}
		else if (str[i] && check)
			write(fd, &str[i], 1);
	}
	ft_putchar_fd('\n', fd);
}
