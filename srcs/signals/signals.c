/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:01 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/20 18:07:44 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Ignores signals acordingly "CTRL-C", "CTRL-Z", "CTRL-\"

/*void	ignore_signal(int signal)
{
	struct sigaction	sa;
	
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	if (sigaction(signal, &sa, NULL) == -1)
		ft_putendl_fd("Error: sigaction failure.\n", 2);
}

void	signal_receiver(int signal)
{
	struct sigaction	sa;
	if (signal == SIGINT)
		
}*/