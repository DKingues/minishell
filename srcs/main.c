/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:02 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/14 17:49:28 by rmota-ma         ###   ########.fr       */
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
	char *last;
	
	//ignore_shell_signal();
	if (ac != 1)
		return (ft_printf("No arguments are needed\n"), 1);
	init_shell(ev);
	last = ft_strdup("");
	while(1)
	{
		line = readline("minishell>");
		if (((ft_strncmp(line, last, ft_strlen(line)) || ac) && line[0] && line[0] != '\n'))
		{
			add_history(line);
			ac = 0;
		}
		if(last)
			free(last);
		last = ft_strdup(line);
	}
	return (0);
}

/* if(!ft_strncmp(line, "clear history", 13))
			rl_clear_history(); */