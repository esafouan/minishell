/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:57:02 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/22 23:22:04 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**expanding_utils(t_env **env, t_pars *mini)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = *env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	temp = *env;
	mini->env = malloc(sizeof(char *) * i + 1);
	if (!mini->env)
		return (NULL);
	i = -1;
	while (temp)
	{
		mini->env[++i] = temp->data;
		temp = temp->next;
	}
	mini->env[i] = NULL;
	return (mini->env);
}

void	exp_env(t_pars *mini, t_env **env)
{
	if (!mini->env)
		return ;
	mini->env = expanding_utils(env, mini);
}

char	*help_expanding(char *str, int j, char *env, char **envir)
{
	char	*envirement;

	envirement = ft_calloc(1, 1);
	envirement = ft_strjoin1(envirement, ((env + j + 1)));
	if (str[j] == '$')
	{
		envirement = ft_strjoin(envirement, expanding(str + j + 1, envir));
	}
	else if (str[j] && str[j] != '$' && str[j] != 34 && str[j] != 39)
		envirement = ft_strjoin(envirement, str + j);
	return (envirement);
}

int	search_exp(char *input, char *env)
{
	int	j;

	j = 0;
	while (input[j] && input[j] != 34 && input[j] != 39 && env[j] != '=')
	{
		if (env[j] == input[j])
			j++;
		else
			break ;
	}
	return (j);
}

char	*expanding(char *str, char **env)
{
	char	*envirement;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = count_variables(str);
	envirement = ft_calloc(1, 1);
	while (env[i])
	{
		j = search_exp(str, env[i]);
		if (env[i][j] == '=' && (str[j] == '$' || str[j] == 39 || str[j] == 0
				|| str[j] == 34))
			envirement = help_expanding(str, j, env[i], env);
		else if (*envirement)
			while (str[j] && str[j] != 34 && str[j] != 39)
				j++;
		i++;
	}
	if ((*(str + j) == 34 || *(str + j) == 39) && count == 0)
		envirement = ft_strjoin1(envirement, str + j);
	return (envirement);
}
