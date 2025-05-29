/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:02 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/23 20:07:45 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_banner() {
	ft_printf(1, "\033[1;95m __________________________________________________________________\n");
	ft_printf(1, "|  \033[1;96m __  __ _____ _   _ _____  _____  _    _ ______ _      _        \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m|  \\/  |_   _| \\ | |_   _|/ ____\\| |  | |  ____| |    | |       \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m| \\  / | | | |  \\| | | | | |____ | |__| | |__  | |    | |       \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m| |\\/| | | | |   ` | | |  \\____ \\|  __  |  __| | |    | |       \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m| |  | |_| |_| |\\  |_| |_ _____| | |  | | |____| |____| |____   \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m|_|  |_|_____|_| \\_|_____|\\_____/|_|  |_|______|______|______|  \033[1;35m|\n");
	ft_printf(1, "\033[1;95m|__________________________________________________________________|\n\n");
	ft_printf(1, "\033[1;95m                          M I N I S H E L L\n\n");
	ft_printf(1, "\033[1;95m                                 b y       \n\n");
	ft_printf(1, "\033[1;92m                         rmota-ma & dicosta-       \033[0m\n\n");
}

int parser(char *line)
{
	if (syntax_check(line) == 0)
		return (0);
	if (expand_check(line))
		line = expand_caller(line);
	t_token *token;
	
	token = assign_token(line);
	while (token)
	{
		ft_printf(1, "VALUE:[%s]\tTYPE: [%d]\n", token->value, token->type);
		token = token->next;
	}
	return (1);
}

int	main(int ac, char **av, char **ev)
{
	(void)av;
	char *line;
	if (ac != 1)
		return (ft_printf(1, "No arguments are needed\n"), 1);
	print_banner();
	init_shell(ev);
	while(1)
	{
		line = readline("minishell ▸ ");
		if (parser(line) == 0)
			ft_printf(1, "");
		if (!ft_strcmp("exit", line))
		{
			free(line);
			ft_free_split(shell()->env);
			ft_free_split(shell()->exp);
			exit(0);
		}
		free(line);
	}
	return (0);
}
