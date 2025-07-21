/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:23:17 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/21 17:50:40 by rmota-ma         ###   ########.fr       */
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
	singleton_free(0);
	close_fds();
	if (execve(path, args, shell()->env) == -1)
	{
		if (!cmd[0] || !check_loop(path))
		{
			ft_printf(2, "minishell: %s: command not found\n", cmd);
			shell()->exit = 127;
		}
		else
		{
			if (!access(path, F_OK))
				exec_err(path, temp);
			else
			{
				temp = ft_nfstrjoin("minishell: ", path);
				perror(temp);
				free(temp);
				shell()->exit = 127;
			}
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

	temp = NULL;
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
		temp = ft_strjoin(find_home(), cmd->value + 1);
		path = find_path(temp, 0);
		free(temp);
	}
	else
		path = find_path(cmd->value, 0);
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

void	execute(t_tree	*cmd)
{
	char	*path;
	char	**args;
	char	*temp;

	path = path_check(cmd);
	if (!path)
		return ;
	if (access(path, F_OK) && access(path, X_OK))
	{
		temp = ft_strdup(path);
		path = search_alias(path);
		if (!ft_strncmp(temp, path, ft_strlen(path)))
		{
			args = args_join(cmd, 0);
			free(temp);
		}
		else
		{
			args = args_except(cmd, path, temp);
			path = find_path(args[0], 0);
		}
	}
	else
		args = args_join(cmd, 0);
	execute2(NULL, path, args, ft_strdup(cmd->value));
}
