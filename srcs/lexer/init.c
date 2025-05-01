/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/01 17:32:09 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_shell(char **ev)
{
	int	var;
	int var2;
	
	var = 0;
	var2 = 0;
	if(!ev[0])
	{
		shell()->env = ft_calloc(sizeof(char *), 2);
		shell()->env[0] = ft_strdup(ABS_PATH);
	}
	else
	{		
		while(ev[var])
			var++;
		var = find_path(ev, var);
		if (var == 1)
			shell()->env[0] = ft_strdup(ABS_PATH);
		while (ev[var])
		{
			shell()->env[var] = ft_strdup(ev[var2]);
			var++;
			var2++;
		}
	}
}

int	find_path(char **envp, int var)
{
	int		var2;

	var2 = 0;
	while (ft_strnstr(envp[var2], "PATH", 4) == 0 && envp[var2 + 1])
		var2++;
	if (!envp[var2 + 1])
	{
		shell()->env = ft_calloc(sizeof(char *), var + 2);
		return (1);
	}
	else
	{
		shell()->env = ft_calloc(sizeof(char *), var + 1);
		return(0);
	}
}

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}
