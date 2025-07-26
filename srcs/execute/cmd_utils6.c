/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:46:28 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 17:17:46 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trunc_help(char *temp, char *value)
{
	temp = ft_nfstrjoin("minishell: ", value);
	if (!temp)
	{
		shell()->exit = 1;
		exit_cmd(NULL, 0);
	}
	perror(temp);
	free(temp);
	shell()->exit = 1;
	return (1);
}

void	exp_organize(void)
{
	int	var;

	var = 0;
	while (shell()->exp[var + 1])
	{
		if (shell()->exp[var][0] > shell()->exp[var + 1][0])
		{
			switch_str(var);
			var = -1;
		}
		var++;
	}
	second_organize(0, 0);
}

void	second_organize(int var, int var2)
{
	int	check;

	var = 0;
	while (shell()->exp[var + 1])
	{
		if (shell()->exp[var][0] == shell()->exp[var + 1][0])
		{
			check = 0;
			while (shell()->exp[var + check + 1] && shell()->exp[var + 1]
				&& shell()->exp[var][0] == shell()->exp[var + check + 1][0])
			{
				var2 = 0;
				while (shell()->exp[var][var2] == shell()->exp[var + 1][var2])
					var2++;
				if (shell()->exp[var][var2] > shell()->exp[var + 1][var2])
				{
					switch_str(var);
					var = -1;
					break ;
				}
				check++;
			}
		}
		var++;
	}
}
