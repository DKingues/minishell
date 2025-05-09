/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:02 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/05 13:40:50 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_banner() {
	ft_printf("\033[1;33m __________________________________________________________________\n");
	ft_printf("|  \033[1;36m __  __ _____ _   _ _____  _____  _    _ ______ _      _        \033[1;33m|\n");
	ft_printf("|  \033[1;36m|  \\/  |_   _| \\ | |_   _|/ ____\\| |  | |  ____| |    | |       \033[1;33m|\n");
	ft_printf("|  \033[1;36m| \\  / | | | |  \\| | | | | |____ | |__| | |__  | |    | |       \033[1;33m|\n");
	ft_printf("|  \033[1;36m| |\\/| | | | | . ` | | |  \\____ \\|  __  |  __| | |    | |       \033[1;33m|\n");
	ft_printf("|  \033[1;36m| |  | |_| |_| |\\  |_| |_ _____| | |  | | |____| |____| |____   \033[1;33m|\n");
	ft_printf("|  \033[1;36m|_|  |_|_____|_| \\_|_____|\\_____/|_|  |_|______|______|______|  \033[1;33m|\n");
	ft_printf("\033[1;33m|__________________________________________________________________|\n\n");
	ft_printf("\033[1;35m                          M I N I S H E L L\n\n");
	ft_printf("\033[1;35m                                 b y       \n\n");
	ft_printf("\033[1;32m                         rmota-ma & dicosta-       \033[0m\n\n");
}

int parser(char *line)
{
	assign_token(line);
	return (TRUE);
}


int	main(int ac, char **av, char **ev)
{
	(void)av;
	char *line;
	
	ignore_shell_signal();
	if (ac != 1)
		return (ft_printf("No arguments are needed\n"), 1);
	print_banner();
	init_shell(ev);
	while(1)
	{
		line = readline("minishell>");
		if (parser(line) == false)
			ft_printf("Error: Unknown Command\n");
	}
	return (0);
}
