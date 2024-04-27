/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:49 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/21 23:57:50 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_all(char *str, int fd)
{
	int		n;
	int		cdt;
	char	*buffer;

	n = 1;
	cdt = 1;
	buffer = malloc(BUFFER_SIZE + (size_t)1);
	while (n && cdt)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
			return (ft_free(buffer, str));
		buffer[n] = '\0';
		str = ft_strjoin(str, buffer);
		if (!str)
			return (0);
		cdt = ft_strchr_fd(buffer, '\n');
	}
	ft_free(buffer, 0);
	if (str[0] == 0)
		return (ft_free(str, 0));
	return (str);
}

char	*get_line(char *str1, int *i)
{
	char	*str2;

	*i = 0;
	while (str1[*i] && str1[*i] != '\n')
		*i += 1;
	*i += (str1[*i] == '\n');
	str2 = (char *)malloc(*i + 1);
	ft_strlcpy(str2, str1, *i + 1);
	str2[*i] = '\0';
	return (str2);
}

char	*get_rest(char *rmdr, int *i)
{
	int		len;
	char	*rst;

	rst = NULL;
	if (rmdr[*i])
	{
		len = ft_strlen(rmdr + *i);
		rst = (char *)malloc(len + 1);
		if (!rst)
		{
			*i = -1;
			return (ft_free(rmdr, 0));
		}
		ft_strlcpy(rst, rmdr + *i, len + 1);
	}
	free(rmdr);
	return (rst);
}

char	*get_next_line(int fd)
{
	static char	*rmdr;
	char		*str;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rmdr = get_all(rmdr, fd);
	if (!rmdr)
		return (NULL);
	str = get_line(rmdr, &i);
	if (!str)
		return (NULL);
	rmdr = get_rest(rmdr, &i);
	if (i == -1)
		return (ft_free(str, 0));
	return (str);
}
