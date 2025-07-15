/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:01 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/14 18:02:02 by dicosta-         ###   ########.fr       */
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
	}
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		exit(130);
	}
}

void	choose_signal2(t_sig_struct	level, struct sigaction *sa)
{
	if (level == HDOC)
	{
		sa->sa_handler = heredoc_handler;
		sa->sa_flags = 0;
		if (sigemptyset(&sa->sa_mask) == -1)
			return ;
		sigaction(SIGINT, sa, NULL);
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

	if (level == ROOT)
	{
		sa.sa_handler = root_handler;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) == -1)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (level == CHLD)
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) == -1)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
		choose_signal2(level, &sa);
}
