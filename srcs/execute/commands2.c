/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:30 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/06/24 17:44:20 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_cmd(t_tree	*tree)
{
	int	code;

	if(tree && tree->value && error_syntax(tree->value) && !long_check(tree->value))
	{
		code = ft_atoi(tree->value);
		if(tree->right && tree->value)
			ft_printf(2, "exit\nbash: exit: too many arguments\n");
		else
		{
			tree_free(shell()->tree);
			ft_printf(1, "exit\n");
			exit(code);
		}
	}
	else if (tree && tree->value)
	{
		code = 2;
		ft_printf(2, "exit\nbash: exit: %s: numeric argument required\n", tree->value);
		tree_free(shell()->tree);
		exit(code);
	}
	else
	{
		ft_printf(1, "exit\n");
		tree_free(shell()->tree);
		exit(shell()->exit);
	}
}

void	cd_cmd(char *path)
{
	
	if (path && !access(path, 0))
	{
		chdir(path);
		set_old_path();
		set_new_path();
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
		printf("Error3");
}

char	*find_path(char *cmd)
{
	char	**path;
	char	*line;
	char	*temp;
	int		var;

	var = 0;
	while (ft_strnstr(shell()->env[var], "PATH", 4) == 0 && shell()->env[var + 1])
		var++;
	if (!shell()->env[var + 1])
		return (cmd);
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
	return (ft_free_split(path), cmd);
}
