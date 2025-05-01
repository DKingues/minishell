/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:18:17 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/01 16:01:01 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line)
{
	char **args;
	
	args = ft_split(line, ' ');
	if (quoting_check(args))
		return(ft_printf("Syntax Error\n"), 1);
	return (0);
}

int	quoting_check(char **args)
{
	int	var;
	int	var2;
	int plica;
	int aspas;

	var2 = 0;
	while(args[var2])
	{
		aspas = 0;
		plica = 0;
		var = 0;
		while(args[var2][var])
		{
			if (args[var2][var] == 34)
				aspas++;
			if (args[var2][var] == 39)
				plica++;
			var++;
		}
		if (plica % 2 != 0 || aspas % 2 != 0)
			return (1);
		var2++;
	}
	return (0);
}
