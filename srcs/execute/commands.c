/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:57:02 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/20 15:45:32 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_cmd(int flag, char *msg)
{
	if(msg)
		ft_printf(1, "%s", msg);
	if (!flag)
		ft_printf(1, "\n");
}

void	pwd_cmd(void)
{
	char path[1000];
	printf("%s\n", getcwd(path, sizeof(path)));
}

void	exp_cmd(int flag, char *msg)
{
	int	var;

	var = 0;
	if(!flag)
	{
		while(shell()->exp[var])
		{
			printf("declare -x %s\n", shell()->exp[var]);
			var++;
		}
	}
	else
	{
		shell()->exp = exp_set(msg);
		if (msg[exp_len(msg)] == '=')
			shell()->env = env_set(msg);
		exp_organize();
	}
}

void	unset_cmd(char *msg)
{
	int	var;

	var = 0;
	if(msg)
	{
		if (msg[exp_len(msg)] == '=')
			return ;
		while(shell()->exp[var])
		{
			if(!ft_strncmp(shell()->exp[var], msg, exp_len(msg)))
			{
				if (shell()->exp[var][exp_len(shell()->exp[var])] == '\0' 
					|| shell()->exp[var][exp_len(shell()->exp[var])] == '=')
				{
					if (shell()->exp[var][exp_len(shell()->exp[var])] == '=')
						shell()->env = re_write_env(msg);
					shell()->exp = re_write_exp(msg);
					return ;
				}
			}
			var++;
		}
	}
}

void	env_cmd(void)
{
	int	var;

	var = 0;
	while(shell()->env[var])
	{
		if (shell()->env[var][0])
			printf("%s\n", shell()->env[var]);
		var++;
	}
}
