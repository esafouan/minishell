/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:06 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/21 23:57:07 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*help_fill_exp(char *split, int j, char **env)
{
	char	*tmp;

	j++;
	if (j == 1)
	{
		tmp = split;
		split = expanding(split + j, env);
		free(tmp);
	}
	else if (j > 1)
	{
		tmp = split;
		split = ft_strjoin1(ft_substr(split, 0, j - 1), expanding(split + j,
					env));
		free(tmp);
	}
	return (split);
}

char	*fill_exp(char *str, char **env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			str = help_fill_exp(str, i, env);
		i++;
	}
	return (str);
}

int	ft_number_hd(t_pars **mini)
{
	t_pars	*temp;
	int		i;
	int		j;

	temp = *mini;
	j = 0;
	while (temp)
	{
		i = -1;
		while (temp->file[++i])
		{
			if ((ft_check_redirection(temp->file[i]) == 3
					&& check_hd(temp->file[i])) || checking(temp->file[i]))
				return (j);
			else if (ft_check_redirection(temp->file[i]) == 3)
				j++;
		}
		temp = temp->next_command;
	}
	return (j);
}

int	ft_number_hd1(t_pars **mini)
{
	t_pars	*temp;
	int		i;
	int		j;

	temp = *mini;
	j = 0;
	while (temp)
	{
		i = -1;
		while (temp->file[++i])
		{
			if ((ft_check_redirection(temp->file[i]) == 3
					&& check_hd(temp->file[i])) || checking(temp->file[i]))
				return (j);
			else if (ft_check_redirection(temp->file[i]) == 3)
				j++;
		}
		temp = temp->next_command;
	}
	return (j);
}

void	piping_hd(t_fd *forces, t_pars **mini)
{
	int	i;
	int	j;

	i = 0;
	j = ft_number_hd(mini);
	forces->fd_hd = malloc(sizeof(int *) * j);
	while (i < j)
	{
		forces->fd_hd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	forces->i = 0;
	forces->x = i;
}
