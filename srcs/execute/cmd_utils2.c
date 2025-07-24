/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:40:54 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/24 15:38:30 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	switch_str(int var)
{
	char	*temp;

	temp = ft_strdup(shell()->exp[var]);
	free(shell()->exp[var]);
	shell()->exp[var] = ft_strdup(shell()->exp[var + 1]);
	free(shell()->exp[var + 1]);
	shell()->exp[var + 1] = ft_strdup(temp);
	free(temp);
}

void	exp_helper2000(char **temp)
{
	int	var;

	var = 0;
	ft_free_split(shell()->exp);
	while (temp[var])
		var++;
	shell()->exp = ft_calloc(var + 1, sizeof(char *));
	if (!shell()->exp)
		return ;
	var = 0;
	while (temp[var])
	{
		shell()->exp[var] = ft_strdup(temp[var]);
		var++;
	}
}

char	**re_write_exp(char *msg, int v, int v2)
{
	char	**temp;

	while (shell()->exp[v])
		v++;
	temp = ft_calloc(sizeof(char *), v);
	if (!temp)
		return (NULL);
	v = 0;
	while (shell()->exp[v + v2])
	{
		if (!ft_strncmp(shell()->exp[v + v2], msg, exp_len(msg)))
		{
			if (!shell()->exp[v + v2][exp_len(shell()->exp[v + v2])]
				|| shell()->exp[v + v2][exp_len(shell()->exp[v + v2])] == '=')
				v2++;
		}
		if (shell()->exp[v + v2])
		{
			temp[v] = ft_strdup(shell()->exp[v + v2]);
			v++;
		}
	}
	ft_free_split(shell()->exp);
	return (temp);
}

void	env_helper2000(char **temp)
{
	int	var;

	var = 0;
	ft_free_split(shell()->env);
	while (temp[var])
		var++;
	shell()->env = ft_calloc(var + 1, sizeof(char *));
	if (!shell()->env)
		return ;
	var = 0;
	while (temp[var])
	{
		shell()->env[var] = ft_strdup(temp[var]);
		var++;
	}
}

char	**re_write_env(char *msg, int v, int v2)
{
	char	**temp;

	while (shell()->env[v])
		v++;
	temp = ft_calloc(sizeof(char *), v);
	if (!temp)
		return (NULL);
	v = 0;
	while (shell()->env[v + v2])
	{
		if (!ft_strncmp(shell()->env[v + v2], msg,
				exp_len(shell()->env[v + v2]) - 1))
		{
			if (shell()->env[v][exp_len(shell()->env[v + v2])] == '\0'
					|| shell()->env[v][exp_len(shell()->env[v + v2])] == '=')
				v2++;
		}
		if (shell()->env[v + v2])
		{
			temp[v] = ft_strdup(shell()->env[v + v2]);
			v++;
		}
	}
	ft_free_split(shell()->env);
	return (temp);
}
