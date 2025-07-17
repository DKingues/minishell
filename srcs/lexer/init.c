/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/16 18:37:13 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(char **ev)
{
	init_env(ev);
	init_exp(ev);
	init_alias();
	shell()->count = 0;
	shell()->tree = NULL;
	shell()->hist = ft_calloc(sizeof(char *), 1);
	shell()->exit = 0;
	shell()->pipe_count = 0;
	shell()->in = 0;
	shell()->out = 0;
	shell()->alias = NULL;
}

void	init_env(char **ev)
{
	int	var;
	
	var = 0;
	if (ev[0])
	{
		while (ev[var])
			var++;
		shell()->env = ft_calloc(sizeof(char *), var + 1);
		var = 0;
		while (ev[var])
		{
			shell()->env[var] = ft_strdup(ev[var]);
			var++;
		}
		lvl_upd();
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
	if (ev[0])
	{
		while (ev[var])
			var++;
		shell()->exp = ft_calloc(sizeof(char *), var + 1);
		var = 0;
		while (ev[var])
		{
			shell()->exp[var] = ft_strdup(ev[var]);
			var++;
		}
		exp_organize();
		exp_lvl();
		shell()->exp = quoting_set();
	}
	else
	{
		shell()->exp = ft_calloc(sizeof(char *), 1);
		shell()->exp[0] = ft_calloc(sizeof(char), 1);
	}
}

void	lvl_upd(void)
{
	int		var;
	int		lvl;
	char	*temp;

	var = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "SHLVL=", 6))
		{
			if (shell()->env[var][6] == '-'
				|| ft_atoui(shell()->env[var] + 6) >= INT_MAX)
				lvl = -1;
			else
				lvl = ft_atoi(shell()->env[var] + 6);
			temp = ft_itoa(lvl + 1);
			free(shell()->env[var]);
			shell()->env[var] = ft_strdup("SHLVL=");
			shell()->env[var] = ft_strjoin(shell()->env[var], temp);
			free(temp);
			break ;
		}
		var++;
	}
}

void	exp_lvl(void)
{
	int		var;
	int		lvl;
	char	*temp;

	var = 0;
	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], "SHLVL=", 6))
		{
			if (shell()->exp[var][6] == '-'
				|| ft_atoui(shell()->exp[var] + 6) >= INT_MAX)
				lvl = -1;
			else
				lvl = ft_atoi(shell()->exp[var] + 6);
			temp = ft_itoa(lvl + 1);
			free(shell()->exp[var]);
			shell()->exp[var] = ft_strdup("SHLVL=");
			shell()->exp[var] = ft_strjoin(shell()->exp[var], temp);
			free(temp);
			break ;
		}
		var++;
	}
}

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}
