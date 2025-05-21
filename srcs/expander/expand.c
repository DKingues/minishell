/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:47:46 by scorpot           #+#    #+#             */
/*   Updated: 2025/05/14 16:20:09 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_arg(char *arg)
{
	int	var;
	int	len;
	char *temp;

	var = 0;
	if (arg[1] == '?' && arg[2] == '\0')
		return(ft_itoa(shell()->exit));
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
				len++;
			else
				return(shell()->env[var] + len + 1);
		}
		var++;
	}
	return(NULL);
}
