/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorpot <scorpot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/02 12:15:33 by scorpot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_shell(char **ev)
{
	init_env(ev);
}

void	init_env(char **ev)
{
	int	var;
	
	var = 0;
	if(ev[0])
	{
		while(ev[var])
			var++;
		shell()->env = ft_calloc(sizeof(char *), var + 1);
		var = 0;
		while (ev[var])
		{
			shell()->env[var] = ft_strdup(ev[var]);
			var++;
		}
	}
	else
	{
		shell()->env = ft_calloc(sizeof(char *), 1);
		shell()->env[0] = ft_calloc(sizeof(char), 1);
	}
}

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}
