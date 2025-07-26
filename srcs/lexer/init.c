/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 18:11:47 by rmota-ma         ###   ########.fr       */
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

void	init_shell(char **ev)
{
	init_env(ev);
	init_exp(ev);
	init_alias();
	shell()->proc_id = getpid_self();
	shell()->count = 0;
	shell()->tree = NULL;
	shell()->hist = ft_calloc(sizeof(char *), 2);
	if (!shell()->hist)
		malloc_err(NULL, "malloc");
	shell()->hist[0] = ft_strdup("");
	if (!shell()->hist[0])
		malloc_err(NULL, "malloc");
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
		lvl_upd(0);
	}
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

void	init_exp(char **ev)
{
	int	var;

	var = 0;
	if (ev[0])
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
		exp_lvl(0);
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
			if (!temp)
			{
				if (shell()->env)
					ft_free_split(shell()->env);
				exit(1);
			}
			free(shell()->env[var]);
			shell()->env[var] = ft_strdup("SHLVL=");
			temp3 = ft_strjoin(shell()->env[var], temp);
			if (!temp3)
			{
				if (temp)
					free(temp);
				if (shell()->env)
					ft_free_split(shell()->env);
				exit(1);
			}
			shell()->env[var] = ft_strdup(temp3);
			if (!shell()->env[var])
			{
				if (temp3)
					free(temp3);
				if (temp)
					free(temp);
				if (shell()->env)
					ft_free_split(shell()->env);
				exit(1);
			}
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
			if (!temp)
			{
				if (shell()->env)
					ft_free_split(shell()->env);
				if (shell()->exp)
					ft_free_split(shell()->exp);
				exit(1);
			}
			free(shell()->exp[var]);
			shell()->exp[var] = ft_strdup("SHLVL=");
			temp3 = ft_strjoin(shell()->exp[var], temp);
			if (!temp3)
			{
				if (temp)
					free(temp);
				if (shell()->env)
					ft_free_split(shell()->env);
				if (shell()->exp)
					ft_free_split(shell()->exp);
				exit(1);
			}
			shell()->exp[var] = ft_strdup(temp3);
			if (!shell()->env[var])
			{
				if (temp3)
					free(temp3);
				if (temp)
					free(temp);
				if (shell()->env)
					ft_free_split(shell()->env);
				if (shell()->exp)
					ft_free_split(shell()->exp);
				exit(1);
			}
			free(temp3);
			free(temp);
			break ;
		}
		var++;
	}
}
