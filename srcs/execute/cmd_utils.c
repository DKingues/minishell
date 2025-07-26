/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:36:39 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 17:41:36 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**exp_set(char *msg, char **temp, int var)
{
	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], msg, exp_len(msg)))
			return (exp_redef(var, msg, 0));
		var++;
	}
	temp = ft_calloc(sizeof(char *), var + 2);
	if (!temp)
		malloc_err(NULL, "malloc");
	var = 0;
	while (shell()->exp[var])
	{
		temp[var] = ft_strdup(shell()->exp[var]);
		if (!temp[var])
			malloc_err(temp, "malloc");
		var++;
	}
	if (msg[exp_len(msg)] == '=')
		temp[var] = exp_strdup(msg);
	else
		temp[var] = ft_strdup(msg);
	if (!temp[var])
		malloc_err(temp, "malloc");
	return (ft_free_split(shell()->exp), temp);
}

char	**env_set(char *msg)
{
	char	**temp;
	int		var;

	var = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], msg, exp_len(msg)))
			return (env_redef(var, msg, 0));
		var++;
	}
	temp = ft_calloc(sizeof(char *), var + 2);
	if (!temp)
		malloc_err(NULL, "malloc");
	var = 0;
	while (shell()->env[var])
	{
		temp[var] = ft_strdup(shell()->env[var]);
		if (!temp[var])
			malloc_err(temp, "malloc");
		var++;
	}
	temp[var] = ft_strdup(msg);
	if (!temp[var])
		malloc_err(temp, "malloc");
	return (ft_free_split(shell()->env), temp);
}

char	**exp_redef(int var2, char *msg, int var)
{
	char	**temp;

	while (shell()->exp[var])
		var++;
	temp = ft_calloc(sizeof(char *), var + 1);
	if (!temp)
		malloc_err(NULL, "malloc");
	var = 0;
	while (shell()->exp[var])
	{
		if (var == var2)
		{
			if (msg[exp_len(msg)] != '='
				&& shell()->exp[var][exp_len(shell()->exp[var])] == '=')
				temp[var] = ft_strdup(shell()->exp[var]);
			else
				temp[var] = exp_strdup(msg);
		}
		else
			temp[var] = ft_strdup(shell()->exp[var]);
		if (!temp[var])
			malloc_err(temp, "malloc");
		var++;
	}
	return (ft_free_split(shell()->exp), temp);
}

char	**env_redef(int var2, char *msg, int var)
{
	char	**temp;

	while (shell()->env[var])
		var++;
	temp = ft_calloc(sizeof(char *), var + 1);
	if (!temp)
		malloc_err(NULL, "malloc");
	var = 0;
	while (shell()->env[var])
	{
		if (var == var2)
		{
			if (msg[exp_len(msg)] != '='
				&& shell()->env[var][exp_len(shell()->env[var])] == '=')
				temp[var] = ft_strdup(shell()->env[var]);
			else
				temp[var] = ft_strdup(msg);
		}
		else
			temp[var] = ft_strdup(shell()->env[var]);
		if (!temp[var])
			malloc_err(temp, "malloc");
		var++;
	}
	return (ft_free_split(shell()->env), temp);
}

size_t	exp_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	return (i);
}
