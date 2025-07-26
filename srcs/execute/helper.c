/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:35:48 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 15:03:41 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_check(char *flags, char *valid)
{
	int	var;
	int	var2;

	var = 1;
	if (!flags[1])
		return (1);
	while (flags[var])
	{
		var2 = 0;
		while (valid[var2])
		{
			if (flags[var] != valid[var2])
				return (1);
			var2++;
		}
		var++;
	}
	return (0);
}

char	**args_join(t_tree	*cmd, int var)
{
	char	*home;
	char	**res;
	t_tree	*temp;

	temp = cmd;
	home = find_home_alias();
	while (temp)
	{
		var++;
		temp = temp->right;
	}
	res = ft_calloc(sizeof(char *), var + 1);
	if (!res)
	{
		shell()->exit = 1;
		exit_cmd(NULL, 0);
	}
	var = 0;
	while (cmd)
	{
		if (cmd->value[0] == '~' && cmd->value[1] == '/')
			res[var] = ft_nfstrjoin(home, cmd->value + 1);
		else
			res[var] = ft_strdup(cmd->value);
		if (!res[var])
		{
			ft_free_split(res);
			free(home);
			shell()->exit = 1;
			exit_cmd(NULL, 0);
		}
		cmd = cmd->right;
		var++;
	}
	return (free(home), res);
}

char	*search_alias(char *path)
{
	int		var;
	int		len;

	var = 0;
	while (shell()->alias[var])
	{
		len = exp_len(shell()->alias[var]);
		if (!ft_strncmp(path, shell()->alias[var],
				len) && len >= 1)
		{
			free(path);
			path = ft_strdup(shell()->alias[var]
					+ exp_len(shell()->alias[var]) + 1);
			if (!path)
			{
				shell()->exit = 1;
				exit_cmd(NULL, 0);
			}
			return (path);
		}
		var++;
	}
	return (path);
}

char	**split_redef(char **args, t_tree *cmd)
{
	int		var;
	t_tree	*temp2;
	char	**temp;

	var = 0;
	temp2 = cmd->right;
	while (args[var])
		var++;
	while (temp2)
	{
		temp2 = temp2->right;
		var++;
	}
	temp = ft_calloc(sizeof(char *), var + 1);
	if (!temp)
	{
		shell()->exit = 1;
		exit_cmd(NULL, 0);
	}
	var = 0;
	while (args[var])
	{
		temp[var] = ft_strdup(args[var]);
		if (!temp[var])
		{
			ft_free_split(args);
			ft_free_split(temp);
			shell()->exit = 1;
			exit_cmd(NULL, 0);
		}
		var++;
	}
	temp2 = cmd->right;
	return (split_redef2(temp2, temp, args, var));
}

char	**split_redef2(t_tree *temp2, char **temp, char **args, int var)
{
	while (temp2)
	{
		temp[var] = ft_strdup(temp2->value);
		if (!temp[var])
		{
			ft_free_split(args);
			ft_free_split(temp);
			shell()->exit = 1;
			exit_cmd(NULL, 0);
		}
		var++;
		temp2 = temp2->right;
	}
	ft_free_split(args);
	return (temp);
}
