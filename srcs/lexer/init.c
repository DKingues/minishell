/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 19:17:50 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	shell()->safe_home = find_home_alias();
	if (!shell()->safe_home)
	{
		ft_printf(2, "minishell: malloc error\n");
		exit(1);
	}
}

void	lvl_upd2(int var, char *temp, char *temp3)
{
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
}

void	lvl_upd(int var, char *temp)
{
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "SHLVL=", 6))
		{
			if (!ft_isdigit(shell()->env[var][6])
				|| ft_atoui(shell()->env[var] + 6) >= 999)
				temp = ft_itoa(0);
			else
				temp = ft_itoa(ft_atoi(shell()->env[var] + 6) + 1);
			if (ft_atoui(shell()->env[var] + 6) >= 999
				&& ft_atoui(shell()->env[var] + 6) < INT_MAX)
				ft_printf(2, E1 E2, ft_atoui(shell()->env[var] + 6) + 1);
			if (!temp)
			{
				if (shell()->env)
					ft_free_split(shell()->env);
				exit(1);
			}
			lvl_upd2(var, temp, NULL);
			break ;
		}
		var++;
	}
}

void	exp_lvl2(int var, char *temp, char *temp3)
{
	free(shell()->exp[var]);
	shell()->exp[var] = ft_strdup("SHLVL=");
	temp3 = ft_strjoin(shell()->exp[var], temp);
	if (!temp3)
	{
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
		free(temp3);
		free(temp);
		if (shell()->env)
			ft_free_split(shell()->env);
		if (shell()->exp)
			ft_free_split(shell()->exp);
		exit(1);
	}
	free(temp3);
	free(temp);
}

void	exp_lvl(int var, int lvl)
{
	char	*temp;

	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], "SHLVL=", 6))
		{
			if (!ft_isdigit(shell()->env[var][6])
				|| ft_atoui(shell()->exp[var] + 6) >= 999)
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
			exp_lvl2(var, temp, NULL);
			break ;
		}
		var++;
	}
}
