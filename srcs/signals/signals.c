/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:01 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/13 15:10:25 by dicosta-         ###   ########.fr       */
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

void	choose_signal(t_temp_sig_struct level)
{
	struct sigaction sa;
	
	if (level.root == 1)
	{
		sa.sa_handler = root_handler;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) == -1)
			return ;
		sigaction(SIGINT, &sa, NULL);
		//ignore_sig(&sa, SIGQUIT);
	}
	else if (level.root == 0)
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) == -1);
			return ;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		
	}
}
