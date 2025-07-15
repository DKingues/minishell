/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:57:02 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/15 16:13:27 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_cmd(int flag, char *msg)
{
	if(msg)
		ft_printf(1, "%s", msg);
	if (!flag)
		ft_printf(1, "\n");
	//shell()->exit = 0;
}

void	pwd_cmd(void)
{
	char path[1000];
	ft_printf(1, "%s\n", getcwd(path, sizeof(path)));
}

int	exp_checker(char *msg)
{
	int	var;
	int	len;

	var = 0;
	len = exp_len(msg);
	if(len == 0 || (!ft_isalpha(msg[0]) && msg[0] != '_'))
		return (1);
	while(var < len)
	{
		if(!ft_isalnum(msg[var]))
			return (1);
		var++;
	}
	return(0);
}

void	exp_cmd(int flag, char *msg)
{
	int	var;

	var = 0;
	if(!flag)
	{
		while(shell()->exp[var])
		{
			if(shell()->exp[var] && shell()->exp[var][0])
				printf("declare -x %s\n", shell()->exp[var]);
			var++;
		}
	}
	else
	{
		if(exp_checker(msg))
		{
			ft_printf(2, "minishell: export: `%s': not a valid identifier\n", msg);
			shell()->exit = 1;
			return ;
		}
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

void	env_cmd(t_tree *tree)
{
	int	var;

	var = 0;
	if(tree->right && tree->right->value && tree->right->type == ARG)
		ft_printf(2,"env: \'%s\': No such file or directory", tree->right->value);
	while(shell()->env[var])
	{
		if (shell()->env[var][0])
			ft_printf(1, "%s\n", shell()->env[var]);
		var++;
	}
}
