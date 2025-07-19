/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:47:46 by scorpot           #+#    #+#             */
/*   Updated: 2025/07/19 19:41:30 by rmota-ma         ###   ########.fr       */
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
		if (ft_strlen(arg) >= 2)
			temp = ft_strjoin(temp, arg + 2);
		return (temp);
	}
	return (expand_arg_continue(arg, var, len, temp));
}

char	*expand_arg_continue(char *arg, int var, int len, char *temp)
{
	while (shell()->env[var])
	{
		len = exp_len(shell()->env[var]);
		if (!ft_strncmp(shell()->env[var], arg + 1, len))
		{
			if (arg[len] && !ft_isalnum(arg[len + 1]))
			{
				temp = ft_strdup(shell()->env[var] + len + 1);
				temp = ft_strjoin(temp, arg + len + 1);
				return (temp);
			}
			else if (arg[len] && ft_isalnum(arg[len + 1]))
				len++;
			else
			{
				temp = ft_strdup(shell()->env[var] + len + 1);
				return (temp);
			}
		}
		var++;
	}
	return (ft_strdup(""));
}
