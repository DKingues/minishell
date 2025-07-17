/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:36:39 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/17 18:06:16 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**exp_set(char *msg)
{
	char	**temp;
	int		var;

	var = 0;
	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], msg, exp_len(msg)))
			return (exp_redef(var, msg));
		var++;
	}
	temp = ft_calloc(sizeof(char *), var + 2);
	var = 0;
	while (shell()->exp[var])
	{
		temp[var] = ft_strdup(shell()->exp[var]);
		var++;
	}
	if (msg[exp_len(msg)] == '=')
		temp[var] = exp_strdup(msg);
	else
		temp[var] = ft_strdup(msg);
	ft_free_split(shell()->exp);
	return (temp);
}

char	**env_set(char *msg)
{
	char	**temp;
	int		var;

	var = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], msg, exp_len(msg)))
			return (env_redef(var, msg));
		var++;
	}
	temp = ft_calloc(sizeof(char *), var + 2);
	var = 0;
	while (shell()->env[var])
	{
		temp[var] = ft_strdup(shell()->env[var]);
		var++;
	}
	temp[var] = ft_strdup(msg);
	ft_free_split(shell()->env);
	return (temp);
}

char	**exp_redef(int var2, char *msg)
{
	int		var;
	char	**temp;

	var = 0;
	while (shell()->exp[var])
		var++;
	temp = ft_calloc(sizeof(char *), var + 1);
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
		var++;
	}
	ft_free_split(shell()->exp);
	return (temp);
}

char	**env_redef(int var2, char *msg)
{
	int		var;
	char	**temp;

	var = 0;
	while (shell()->env[var])
		var++;
	temp = ft_calloc(sizeof(char *), var + 1);
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
		var++;
	}
	ft_free_split(shell()->env);
	return (temp);
}

size_t	exp_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	return (i);
}
