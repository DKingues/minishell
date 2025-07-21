/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/21 17:58:09 by rmota-ma         ###   ########.fr       */
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
	shell()->hist = ft_calloc(sizeof(char *), 2);
	shell()->hist[0] = ft_strdup("");
	shell()->exit = 0;
	shell()->pipe_count = 0;
	shell()->in = 0;
	shell()->out = 0;
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
		if (!shell()->env)
			exit(1);
		var = 0;
		while (ev[var])
		{
			shell()->env[var] = ft_strdup(ev[var]);
			var++;
		}
		lvl_upd(0);
	}
	else
	{
		shell()->env = ft_calloc(sizeof(char *), 1);
		if (!shell()->env)
			exit(1);
		shell()->env[0] = ft_strdup("");
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
		exp_lvl(0);
		shell()->exp = quoting_set();
	}
	else
	{
		shell()->exp = ft_calloc(sizeof(char *), 1);
		shell()->exp[0] = ft_strdup("");
	}
}

void	lvl_upd(int var)
{
	int		lvl;
	char	*temp;
	char	*temp3;

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
			temp3 = ft_strjoin(shell()->env[var], temp);
			shell()->env[var] = ft_strdup(temp3);
			free(temp3);
			free(temp);
			break ;
		}
		var++;
	}
}

void	exp_lvl(int var)
{
	int		lvl;
	char	*temp;
	char	*temp3;

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
			temp3 = ft_strjoin(shell()->exp[var], temp);
			shell()->exp[var] = ft_strdup(temp3);
			free(temp3);
			free(temp);
			break ;
		}
		var++;
	}
}
