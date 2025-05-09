/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorpot <scorpot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/09 14:15:28 by scorpot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_shell(char **ev)
{
	init_env(ev);
	shell()->exit = 0;
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

void	init_exp(char **ev)
{
	int	var;
	
	var = 0;
	if(ev[0])
	{
		while(ev[var])
			var++;
		shell()->exp = ft_calloc(sizeof(char *), var + 1);
		var = 0;
		while (ev[var])
		{
			shell()->exp[var] = ft_strdup(ev[var]);
			var++;
		}
		exp_organize();
		shell()->exp = quoting_set();
	}
	else
	{
		shell()->exp = ft_calloc(sizeof(char *), 1);
		shell()->exp[0] = ft_calloc(sizeof(char), 1);
	}
}

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}
