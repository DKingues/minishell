/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:47:46 by scorpot           #+#    #+#             */
/*   Updated: 2025/08/04 20:11:23 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_arg(char *arg)
{
	int		var;
	int		len;
	char	*temp;

	var = 0;
	len = 0;
	temp = NULL;
	if (arg[1] == '?')
	{
		temp = ft_itoa(shell()->exit);
		if (!temp)
			malloc_err(NULL, "malloc");
		if (ft_strlen(arg) >= 2)
			temp = ft_strjoin(temp, arg + 2);
		if (!temp)
			malloc_err(NULL, "malloc");
		return (temp);
	}
	else if (arg[0] == '$' && arg[1] == '$')
		return (pid_expand(temp, arg));
	return (expand_arg_continue(arg, var, len, temp));
}

char	*edge_expansion(char *arg)
{
	int		var;
	char	*res;

	var = 1;
	if (arg[1] && (arg[1] == '_' || ft_isalpha(arg[1])))
		return (ft_strdup("\1"));
	res = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!res)
		malloc_err(NULL, "malloc");
	res[0] = '\1';
	while (arg[var + 1])
	{
		res[var] = arg[var + 1];
		var++;
	}
	return (res);
}

char	*expand_arg_continue(char *arg, int var, int len, char *temp)
{
	while (shell()->exp[var])
	{
		len = exp_len(shell()->exp[var]);
		if (!ft_strncmp(shell()->exp[var], arg + 1, len)
			&& shell()->exp[var][len] == '=')
		{
			if (arg[len] && !ft_isalnum(arg[len + 1]))
				return (normie_expander(temp, var, len, arg));
			else if (arg[len] && ft_isalnum(arg[len + 1]))
				len++;
			else
			{
				temp = ft_strdup(shell()->exp[var] + len + 1);
				if (!temp)
				{
					free(arg);
					malloc_err(NULL, "malloc");
				}
				return (temp);
			}
		}
		var++;
	}
	return (edge_expansion(arg));
}

char	*find_final(char *cmd, char *temp)
{
	if (cmd)
	{
		temp = ft_strdup(cmd);
		if (!temp)
			malloc_err(NULL, "malloc");
	}
	else
		temp = NULL;
	return (temp);
}

int	right_len(t_tree *temp)
{
	int	var;

	var = 0;
	while (temp)
	{
		var++;
		temp = temp->right;
	}
	return (var);
}
