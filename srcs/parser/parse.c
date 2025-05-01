/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:18:17 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/01 18:20:34 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(char *line)
{
	char **args;
	
	args = ft_split(line, ' ');
	if (quoting_check(args))
		return(ft_free_split(args), ft_printf("Syntax Error\n"), 1);
	args = quoting_break(args);
	ft_free_split(args);
	return (0);
}

int	quoting_check(char **args)
{
	long	var;

	shell()->count = 0;
	shell()->aspas = 0;
	shell()->plica = 0;
	while(args[shell()->count])
	{
		var = 0;
		while(args[shell()->count][var])
		{
			if (args[shell()->count][var] == 34)
				shell()->aspas++;
			if (args[shell()->count][var] == 39)
				shell()->plica++;
			var++;
		}
		shell()->count++;
	}
	if (shell()->plica % 2 != 0 || shell()->aspas % 2 != 0)
			return (1);
	return (0);
}

char **quoting_break(char **args)
{
	return (args);
}
