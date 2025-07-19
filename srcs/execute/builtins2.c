/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:29:47 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/19 19:03:41 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	history_parser(t_tree *temp, int flag)
{
	temp = temp->right;
	if (!temp || !temp->value)
	{
		while (shell()->hist[flag])
		{
			ft_printf(1, "    %d  %s\n", flag + 1, shell()->hist[flag]);
			flag++;
		}
		return ;
	}
	else if (temp->value[0] == '-')
		shell()->hist = hist_manage("", !flag_check(temp->value, "c"));
	else
		history_parser2(temp, 0, 0);
}

void	builtin_exec2(t_tree *temp)
{
	if (!ft_strncmp(temp->value, "unset", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		while (temp)
		{
			unset_cmd(temp->value);
			temp = temp->right;
		}
	}
	else if (!ft_strncmp(temp->value, "pwd", ft_strlen(temp->value) + 1))
		pwd_cmd();
	else if (!ft_strncmp(temp->value, "env", ft_strlen(temp->value) + 1))
		env_cmd(temp);
	else if (!ft_strncmp(temp->value, "cd", ft_strlen(temp->value) + 1))
		cd_parser(temp);
	else if (!ft_strncmp(temp->value, "history", ft_strlen(temp->value) + 1))
		history_parser(temp, 0);
	dup2(shell()->in, 0);
	dup2(shell()->out, 1);
	close_fds();
}

void	builtin_exec(t_tree *tree)
{
	t_tree	*temp;
	t_tree	*temp2;
	char	*str;

	temp = tree;
	str = NULL;
	if (!ft_strncmp(temp->value, "export", ft_strlen(temp->value) + 1))
		exp_parser(temp);
	else if (!ft_strncmp(temp->value, "echo", ft_strlen(temp->value) + 1))
	{
		temp2 = temp->right;
		echo_parser(temp2, 0, str);
	}
	else if (!ft_strncmp(temp->value, "exit", ft_strlen(temp->value) + 1))
	{
		if (tree->right)
			exit_cmd(tree->right, 0);
		else
			exit_cmd(NULL, 0);
	}
	builtin_exec2(temp);
}

int	check_loop(char *path)
{
	int	var;
	int	check;

	check = 0;
	var = 0;
	while (path[var])
	{
		if (path[var] == '/')
			check = 1;
		var++;
	}
	return (check);
}
