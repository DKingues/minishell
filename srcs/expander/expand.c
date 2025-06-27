/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:47:46 by scorpot           #+#    #+#             */
/*   Updated: 2025/06/25 20:30:36 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_arg(char *arg)
{
	int	var;
	int	len;
	char *temp;

	var = 0;
	if (arg[1] == '?')
	{
		temp = ft_itoa(shell()->exit);
		if (ft_strlen(arg) >= 2)
			temp = ft_strjoin(temp, arg + 2);
		return (free(arg), temp);
	}
	while(shell()->env[var])
	{
		len = exp_len(shell()->env[var]);
		if (!ft_strncmp(shell()->env[var], arg + 1, len))
		{
			if (arg[len] && !ft_isalnum(arg[len + 1]))
			{
				temp = ft_strdup(shell()->env[var] + len + 1);
				temp = ft_strjoin(temp, arg + len + 1);
				return(free(arg), temp);
			}
			else if (arg[len] && ft_isalnum(arg[len + 1]))
				len++;
			else
			{
				temp = ft_strdup(shell()->env[var] + len + 1);				
				return(free(arg), temp);
			}
		}
		var++;
	}
	return(free(arg), ft_strdup(""));
}
