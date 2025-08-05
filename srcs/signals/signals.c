/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:01 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/04 19:56:15 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	root_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		shell()->exit = 130;
	}
}

void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		if (shell()->pids)
			free(shell()->pids);
		exit(130);
	}
	else if (signal == SIGQUIT)
	{
		ft_printf(1, "\n");
		if (shell()->pids)
			free(shell()->pids);
		exit(131);
	}
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		singleton_free(1);
		exit(130);
	}
}

void	choose_signal2(t_sig_struct	level, struct sigaction *sa)
{
	if (level == HDOC)
	{
		sa->sa_handler = heredoc_handler;
		sigaction(SIGINT, sa, NULL);
		sa->sa_handler = SIG_IGN;
		sigaction(SIGQUIT, sa, NULL);
	}
	else if (level == IGNORE)
	{
		sa->sa_handler = SIG_IGN;
		sigaction(SIGINT, sa, NULL);
		sigaction(SIGQUIT, sa, NULL);
	}
}

void	choose_signal(t_sig_struct level)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1)
		return ;
	if (level == ROOT)
	{
		sa.sa_handler = root_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (level == CHLD)
	{
		sa.sa_handler = child_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
		choose_signal2(level, &sa);
}
