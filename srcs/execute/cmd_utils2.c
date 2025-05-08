/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:40:54 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/07 16:57:21 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exp_organize(void)
{
	int	var;
	
	var = 0;
	while(shell()->exp[var + 1])
	{
		if(shell()->exp[var][0] > shell()->exp[var + 1][0])
		{
			switch_str(var);
			var = 0;
		}
		var++;
	}
	second_organize(0,0);
}

void	second_organize(int	var, int var2)
{
	int	check;

	var = 0;
	while(shell()->exp[var + 1])
	{
		if(shell()->exp[var][0] == shell()->exp[var + 1][0])
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

void	switch_str(int var)
{
	char *temp;
	
	temp = ft_strdup(shell()->exp[var]);
	free(shell()->exp[var]);
	shell()->exp[var] = ft_strdup(shell()->exp[var + 1]);
	free(shell()->exp[var + 1]);
	shell()->exp[var + 1] = ft_strdup(temp);
	free(temp);
}

char **re_write_exp(char *msg)
{
	int	var;
	char **temp;
	
	var = 0;
	while(shell()->exp[var])
		var++;
	temp = ft_calloc(sizeof(char*), var);
	var = 0;
	while(shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], msg, exp_len(msg)))
		{
			if (shell()->exp[var][exp_len(shell()->exp[var])] == '\0' 
					|| shell()->exp[var][exp_len(shell()->exp[var])] == '=')
				var++;
		}
		if (shell()->exp[var])
		{
			temp[var] = ft_strdup(shell()->exp[var]);
			var++;
		}
	}
	ft_free_split(shell()->exp);
	return (temp);
}

char **re_write_env(char *msg)
{
	int	var;
	char **temp;
	
	var = 0;
	while(shell()->env[var])
		var++;
	temp = ft_calloc(sizeof(char *), var);
	var = 0;
	while(shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], msg, exp_len(msg)))
		{
			if (shell()->env[var][exp_len(shell()->env[var])] == '=')
				var++;
		}
		if (shell()->env[var])
		{
			temp[var] = ft_strdup(shell()->env[var]);
			var++;
		}
	}
	ft_free_split(shell()->env);
	return (temp);
}