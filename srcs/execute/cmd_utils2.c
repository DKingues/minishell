/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:40:54 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 17:44:50 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	switch_str(int var)
{
	char	*temp;

	temp = ft_strdup(shell()->exp[var]);
	if (!temp)
		malloc_err(NULL, "malloc");
	free(shell()->exp[var]);
	shell()->exp[var] = ft_strdup(shell()->exp[var + 1]);
	if (!shell()->exp[var])
	{
		if (temp)
			free(temp);
		malloc_err(NULL, "malloc");
	}
	free(shell()->exp[var + 1]);
	shell()->exp[var + 1] = ft_strdup(temp);
	if (!shell()->exp[var + 1])
	{
		if (temp)
			free(temp);
		malloc_err(NULL, "malloc");
	}
	free(temp);
}

char	**re_write_exp(char *msg, int v, int v2)
{
	char	**temp;

	while (shell()->exp[v])
		v++;
	temp = ft_calloc(sizeof(char *), v);
	if (!temp)
		malloc_err(NULL, "malloc");
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
			if (!temp[v])
				malloc_err(temp, "malloc");
			v++;
		}
	}
	return (ft_free_split(shell()->exp), temp);
}

char	**re_write_env(char *msg, int v, int v2)
{
	char	**temp;

	while (shell()->env[v])
		v++;
	temp = ft_calloc(sizeof(char *), v);
	if (!temp)
		malloc_err(NULL, "malloc");
	v = 0;
	while (shell()->env[v + v2])
	{
		if (!ft_strncmp(shell()->env[v + v2], msg, exp_len(msg)))
		{
			if (!shell()->env[v + v2][exp_len(shell()->env[v + v2])]
				|| shell()->env[v + v2][exp_len(shell()->env[v + v2])] == '=')
				v2++;
		}
		if (shell()->env[v + v2])
		{
			temp[v] = ft_strdup(shell()->env[v + v2]);
			if (!temp[v])
				malloc_err(temp, "malloc");
			v++;
		}
	}
	return (ft_free_split(shell()->env), temp);
}
