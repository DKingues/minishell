/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:23:17 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 19:16:31 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_err(char *path, char *temp)
{
	DIR	*filedir;

	filedir = NULL;
	if (path)
		filedir = opendir(path);
	if (path && filedir)
		ft_printf(2, "minishell: %s: Is a directory\n", path);
	else
	{
		if (access(path, X_OK))
			temp = ft_nfstrjoin("minishell: ", path);
		else
			temp = ft_nfstrjoin("minishell: ", path);
		if (!temp)
			malloc_err(NULL, "malloc");
		perror(temp);
		free(temp);
	}
	if (filedir)
		free(filedir);
	shell()->exit = 126;
	close_fds();
}

void	execute2(char *temp, char *path, char **args, char *cmd)
{
	if (!cmd)
		malloc_err(NULL, "malloc");
	singleton_free(0);
	close_fds();
	if (execve(path, args, shell()->env) == -1)
	{
		if (!cmd || !cmd[0] || !check_loop(cmd))
		{
			ft_printf(2, "minishell: %s: command not found\n", cmd);
			shell()->exit = 127;
		}
		else
		{
			if (!access(path, F_OK))
				exec_err(cmd, temp);
			else
				else_exec(path);
		}
	}
	ft_free_split(args);
	free(path);
	free(cmd);
}

char	*path_check(t_tree *cmd)
{
	char	*temp;
	char	*path;

	if (is_builtin(cmd->value))
	{
		builtin_exec(cmd);
		if (shell()->pipe_count)
			singleton_free(0);
		close_fds();
		return (NULL);
	}
	if (cmd->value[0] == '~' && cmd->value[1] == '/')
	{
		temp = ft_strdup(shell()->safe_home);
		if (!temp)
			return (NULL);
		temp = ft_strjoin(temp, cmd->value + 1);
		if (!temp)
			malloc_err(NULL, "malloc");
		path = find_path(temp, 0, NULL, NULL);
		free(temp);
	}
	else
		path = find_path(cmd->value, 0, NULL, NULL);
	return (path);
}

char	**args_except(t_tree *cmd, char *path, char *temp)
{
	char	**args;

	args = ft_split(path, ' ');
	args = split_redef(args, cmd);
	free(temp);
	free(path);
	return (args);
}

void	execute(t_tree	*cmd, char *temp, char *path)
{
	char	**args;

	path = path_check(cmd);
	if (!path)
		return ;
	if (access(path, F_OK) && access(path, X_OK))
	{
		temp = ft_strdup(path);
		if (!temp)
			malloc_err(NULL, "malloc");
		path = search_alias(path);
		if (!ft_strncmp(temp, path, ft_strlen(path)))
		{
			args = args_join(cmd, 0);
			free(temp);
		}
		else
		{
			args = args_except(cmd, path, temp);
			path = find_path(args[0], 0, NULL, NULL);
		}
	}
	else
		args = args_join(cmd, 0);
	execute2(NULL, path, args, ft_strdup(cmd->value));
}
