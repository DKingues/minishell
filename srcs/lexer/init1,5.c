/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1,5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:15:11 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/31 16:15:42 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getpid_self(void)
{
	char	*current;
	char	*pid;
	char	path[1000];

	current = ft_strdup(getcwd(path, sizeof(path)));
	if (!current)
		malloc_err(NULL, "malloc");
	chdir("/proc/self");
	pid = ft_strdup(getcwd(path, sizeof(path)) + 6);
	if (!pid)
	{
		if (current)
			free(current);
		malloc_err(NULL, "malloc");
	}
	chdir(current);
	free(current);
	return (pid);
}

void	init_env2(char **ev)
{
	int	var;

	var = 0;
	while (ev[var])
		var++;
	shell()->env = ft_calloc(sizeof(char *), var + 1);
	if (!shell()->env)
	{
		ft_printf(2, "minishell: malloc error\nexit\n");
		exit(1);
	}
	var = 0;
	while (ev[var])
	{
		shell()->env[var] = ft_strdup(ev[var]);
		if (!shell()->env[var])
		{
			ft_printf(2, "minishell: malloc error\nexit\n");
			ft_free_split(shell()->env);
			exit(1);
		}
		var++;
	}
	lvl_upd(0, NULL);
}

void	init_env(char **ev)
{
	if (ev[0])
		init_env2(ev);
	else
	{
		shell()->env = ft_calloc(sizeof(char *), 1);
		if (!shell()->env)
		{
			ft_printf(2, "minishell: malloc error\nexit\n");
			exit(1);
		}
		shell()->env[0] = ft_strdup("");
		if (!shell()->env[0])
		{
			ft_printf(2, "minishell: malloc error\nexit\n");
			ft_free_split(shell()->env);
			exit(1);
		}
	}
}

void	init_exp2(char **ev, int var)
{
	while (ev[var])
		var++;
	shell()->exp = ft_calloc(sizeof(char *), var + 1);
	if (!shell()->exp)
	{
		if (shell()->env)
			ft_free_split(shell()->env);
		exit(1);
	}
	var = 0;
	while (ev[var])
	{
		shell()->exp[var] = ft_strdup(ev[var]);
		if (!shell()->exp[var])
		{
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
		var++;
	}
	exp_organize();
	exp_lvl(0, 0);
}

void	init_exp(char **ev)
{
	if (ev[0])
	{
		init_exp2(ev, 0);
		shell()->exp = quoting_set(0);
	}
	else
	{
		shell()->exp = ft_calloc(sizeof(char *), 1);
		if (!shell()->exp)
		{
			if (shell()->env)
				ft_free_split(shell()->env);
			exit(1);
		}
		shell()->exp[0] = ft_strdup("");
		if (!shell()->exp[0])
		{
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
	}
}
