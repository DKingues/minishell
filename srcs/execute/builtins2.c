/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:29:47 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 17:53:02 by rmota-ma         ###   ########.fr       */
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
	if (temp && !ft_strncmp(temp->value, "unset", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		while (temp)
		{
			if (temp->value)
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
	else
		builtin_exec2(temp);
	dup2(shell()->in, 0);
	dup2(shell()->out, 1);
	close_fds();
}

int	check_loop(char *path)
{
	int	var;

	var = 0;
	while (path[var])
	{
		if (path[var] == '/')
			return (1);
		var++;
	}
	var = 0;
	while (shell()->env[var] && !ft_strnstr(shell()->env[var], "PATH", 4)
		&& shell()->env[var + 1])
		var++;
	if (!shell()->env[var + 1])
		return (1);
	return (0);
}

char	*str_loop(t_tree *temp, char *str)
{
	while (temp)
	{
		str = ft_strjoin(str, " ");
		if (!str)
			malloc_err(NULL, "malloc");
		str = ft_strjoin(str, temp->value);
		if (!str)
			malloc_err(NULL, "malloc");
		temp = temp->right;
	}
	return (str);
}
