/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:01 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/27 16:20:42 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void root_handler(int signal)
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
	if ()
	//free tudo e exit
	exit(127 + SIGINT);
	
}

void	choose_signal(int level)
{
	struct sigaction sa;
	
	if (level.root == 1)
	{
		sa.sa_handler = root_handler;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) == -1)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (level.root == 0)
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) == -1)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		shell()
	}
}
//root
//child
// heredoc
// ign
