/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:23:17 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/20 23:53:51 by dicosta-         ###   ########.fr       */
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

void	execute2(char *temp, char *path, char **args, int check)
{
	check = check_loop(path);
	singleton_free(0);
	close_fds();
	if (execve(path, args, shell()->env) == -1)
	{
		if (!check)
		{
			ft_printf(2, "minishell: %s: command not found\n", path);
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
		path = find_path(temp);
		free(temp);
	}
	else
		path = find_path(cmd->value);
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
			args = args_join(cmd);
			free(temp);
		}
		else
		{
			args = args_except(cmd, path, temp);
			path = find_path(args[0]);
		}
	}
	else
		args = args_join(cmd);
	execute2(NULL, path, args, 0);
}
