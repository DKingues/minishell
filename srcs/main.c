/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorpot <scorpot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:02 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/11 15:59:34 by scorpot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parser(char *line)
{
	assign_token(line);
	return (TRUE);
}


int	main(int ac, char **av, char **ev)
{
	(void)av;
	char *line;
	char *temp;
	//ignore_shell_signal();
	if (ac != 1)
		return (ft_printf("No arguments are needed\n"), 1);
	init_shell(ev);
	while(1)
	{
		line = readline("minishell>");
		temp = expand_arg(line);
		if (temp)
			printf("%s\n", temp);
		/* if (parser(line) == false)
			ft_printf("Error: Unknown Command\n"); */
	}
	return (0);
}
