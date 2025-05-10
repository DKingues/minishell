/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorpot <scorpot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:47:46 by scorpot           #+#    #+#             */
/*   Updated: 2025/05/10 22:48:49 by scorpot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_arg(char *arg)
{
	int	var;
	int	len;
	char *temp;

	var = 0;
	while(shell()->env[var])
	{
		len = exp_len(shell()->env[var]);
		if (!ft_strncmp(shell()->env[var], arg + 1, len))
		{
			if (arg[len] && !ft_isalnum(arg[len + 1]))
			{
				temp = ft_strdup(shell()->env[var] + len + 1);
				arg = ft_strjoin(temp, arg + len + 1);
				return(arg);
			}
			else if (arg[len] && ft_isalnum(arg[len + 1]))
				return(arg);
			else
				return(shell()->env[var] + len + 1);
		}
		var++;
	}
	return(NULL);
}
