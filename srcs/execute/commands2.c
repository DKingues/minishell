/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:30 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/21 13:07:49 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	singleton_free(int exit)
{
	if (exit)
	{
		ft_free_split(shell()->env);
		close_fds();
	}
	ft_free_split(shell()->alias);
	ft_free_split(shell()->hist);
	ft_free_split(shell()->exp);
	if(shell()->docs)
	{
		free(shell()->docs);
	}
	if (shell()->tree)
		tree_free(shell()->tree);
}

void	exit_help(void)
{
	singleton_free(1);
	exit(shell()->exit);
}

void	exit_cmd(t_tree	*tree, int code)
{
	if (tree && tree->value && error_syntax(tree->value)
		&& !long_check(tree->value))
	{
		if (tree->right && tree->value)
		{
			ft_printf(2, "minishell: exit: too many arguments\n");
			shell()->exit = 1;
		}
		else
		{
			code = ft_atoi(tree->value);
			singleton_free(1);
			exit(code);
		}
	}
	else if (tree && tree->value)
	{
		ft_printf(2, "minishell: exit: %s: numeric argument required\n",
			tree->value);
		singleton_free(1);
		exit(2);
	}
	else
		exit_help();
}

void	cd_cmd(char *path)
{
	if (path && !access(path, F_OK) && !access(path, X_OK))
	{
		chdir(path);
		set_old_path(0, 0, 0, NULL);
		set_new_path(0);
	}
	else if (!path)
		mv_home();
	else if (path[0] == '~' && !path[1])
		mv_home();
	else if (path[0] == '-')
		mv_old();
	else if (path[0] == '~' && path[1])
		mv_abs(path);
	else
	{
		ft_printf(2, "minishell: cd: %s: No such file or directory\n", path);
		shell()->exit = 1;
	}
}

char	*find_path(char *cmd)
{
	char	**path;
	char	*line;
	char	*temp;
	int		var;

	var = 0;
	while (ft_strnstr(shell()->env[var], "PATH", 4) == 0
		&& shell()->env[var + 1])
		var++;
	if (!shell()->env[var + 1])
		return (ft_strdup(cmd));
	path = ft_split(shell()->env[var] + 5, ':');
	var = 0;
	while (path[var] != NULL)
	{
		temp = ft_nfstrjoin(path[var], "/");
		line = ft_strjoin(temp, cmd);
		if (access(line, 0) == 0)
			return (ft_free_split(path), line);
		free(line);
		var++;
	}
	if(cmd)
		temp = ft_strdup(cmd);
	else
		temp = NULL;
	return (ft_free_split(path),temp);
}
