/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:35:47 by esafouan          #+#    #+#             */
/*   Updated: 2023/03/28 00:00:50 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT && g_gbl.g_status != 130)
	{
		g_gbl.g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	handle_sigint2(int sig)
{
	if (sig == SIGINT)
	{
		g_gbl.g_status = 131;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	minishell(t_env **envir, t_fd *forces, t_pars *mini)
{
	exp_env(mini, envir);
	if ((*envir)->cmd_count >= 2)
		g_gbl.ex = exec_process(envir, &mini, forces);
	else
	{
		if (!check_builtin(mini))
		{
			g_gbl.ex = ft_exec_builtins(envir, mini, forces);
		}
		else
			g_gbl.ex = exec_path(envir, &mini, forces);
	}
	forces->z = 0;
	closing_hd(forces, &mini);
	free(mini->env);
}

void	mini_shell(t_fd *forces, t_env *envir, char **env, t_pars *mini)
{
	forces->tmpin = dup(0);
	forces->tmpout = dup(1);
	if (env[0])
		minishell(&envir, forces, mini);
	dup2(forces->tmpin, 0);
	close(forces->tmpin);
	dup2(forces->tmpout, 1);
	close(forces->tmpout);
}

int	main(int ac, char **av, char **env)
{
	t_pars	*mini;
	t_help	*pars;
	t_trim	*trim;
	t_env	*envir;
	t_fd	*forces;

	(void)ac;
	(void)av;
	trim = malloc(sizeof(t_trim));
	pars = malloc(sizeof(t_help));
	forces = malloc(sizeof(t_fd));
	convert(&envir, env);
	while (1)
	{
		(signal(SIGINT, handle_sigint), signal(SIGQUIT, SIG_IGN));
		g_gbl.g_status = 1;
		lexer_expander(&envir, forces, pars);
		if (pars->pour == 0)
		{
			mini = last_trim(mini, pars, trim);
			mini_shell(forces, envir, env, mini);
			free_all(mini, pars);
		}
	}
	return (g_gbl.g_status);
}
