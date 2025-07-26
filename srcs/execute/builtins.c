/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:29:13 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 17:41:07 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "env", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "history", ft_strlen(cmd) + 1))
		return (1);
	return (0);
}

void	exp_parser(t_tree *temp)
{
	temp = temp->right;
	if (!temp || !temp->value)
		exp_cmd(0, NULL, 0);
	while (temp)
	{
		exp_cmd(1, temp->value, 0);
		temp = temp->right;
	}
}

void	echo_parser(t_tree *temp, int flag, char *str)
{
	if (temp && temp->value)
	{
		while (temp && temp->value[0] == '-')
		{
			flag = !flag_check(temp->value, "n");
			if (!flag)
				break ;
			temp = temp->right;
		}
		if (!temp && flag)
			return ;
		str = ft_strdup(temp->value);
		if (!str)
			malloc_err(NULL, "malloc");
		temp = temp->right;
		str = str_loop(temp, str);
		echo_cmd(flag, str);
		if (str)
			free(str);
	}
	else
		ft_printf(1, "\n");
}

void	cd_parser(t_tree *temp)
{
	temp = temp->right;
	if (temp && temp->value)
	{
		if (temp->right && temp->right->value)
		{
			ft_printf(2, "minishell: cd: too many arguments\n");
			shell()->exit = 1;
		}
		else
			cd_cmd(temp->value);
		return ;
	}
	else
		cd_cmd(NULL);
}

void	history_parser2(t_tree *temp, int flag, int var)
{
	while (temp->value[flag])
	{
		if (!ft_isdigit(temp->value[flag]))
		{
			ft_printf(2, "minishell: history: %s: numeric argument \
				required\n", temp->value);
			return ;
		}
		flag++;
	}
	flag = ft_atoi(temp->value);
	while (shell()->hist[var])
		var++;
	while (flag > 0)
	{
		var--;
		flag--;
	}
	if (var < 0)
		var = 0;
	while (shell()->hist[var])
	{
		ft_printf(1, "    %d  %s\n", var + 1, shell()->hist[var]);
		var++;
	}
}
