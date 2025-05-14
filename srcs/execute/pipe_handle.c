/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:11:32 by scorpot           #+#    #+#             */
/*   Updated: 2025/05/14 16:21:00 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../minishell.h"

void	pipex(int count, char **args)
{
	int	*pids;
	int	fd[2];

	pids = ft_calloc(sizeof(int), count + 1);
	if (pipe(fd) == -1)
		error();
	pids[0] = fork();
	if (pids[0] < 0)
		error();
	if (pids[0] == 0)
	{
		free(pids);
		first_process(args, fd);
	}
	else
		dup2(fd[0], 0);
	//close missing
	pids = parent(count, args, pids);
	//close missing
	close(0);
	shell()->exit = waitpids(pids, count);
}

void	first_process(char **args, int *fd)
{
	int		infile;
	char	*path;
	char	**cmd1;

	cmd1 = NULL;
	if (!args[2][0])
		error_env(cmd1);
	cmd1 = ft_split(args[2], ' '); // find rule on parsing
	if (!cmd1)
		error();
	path = find_path(cmd1[0]);
	if (args[1]) //1 = write redir flag | check type redir
		redir_input(args[1], args[1]); //1 = write redir flag
	else
		dup2(fd[1], 1);
	if (args[0]) //0 = read redir flag | check type redir
		redir_input(args[0], args[0]); //0 = read redir flag
	close_fds();
	if (execve(path, cmd1, shell()->env) == -1)
		execve_error(path, cmd1);
}

int	*parent(int count, char **args, int *pids)
{
	int	var;
	int	pid1;

	var = 0;
	while (var < count - 2)
	{
		pids[var + 1] = pimping(args[var], pids);
		var++;
	}
	pids[var + 1] = fork();
	if (pids[var + 1] < 0)
		error();
	if (pids[var + 1] == 0)
	{
		free(pids);
		last_process(args, count, 1);
	}
	return (pids[var + 1]);
}

int	pimping(char *cmd1, int *pids)
{
	int	pid1;
	int	fd[2];

	if (pipe(fd) == -1)
		error();
	pid1 = fork();
	if (pid1 < 0)
		error();
	if (pid1 == 0)
	{
		free(pids);
		dup2(fd[1], 1);
		process(cmd1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
	close(fd[0]);
	close(fd[1]);
	return (pid1);
}

void	process(char *argv)
{
	char	**cmd1;
	char	*path;

	cmd1 = NULL;
	if (!argv[0])
	{
		perror("Error");
		close_fds();
		exit(126);
	}
	cmd1 = ft_split(argv, ' ');
	if (!cmd1)
		error();
	path = find_path(cmd1[0]);
	close_fds();
	if (execve(path, cmd1, shell()->env) == -1)
		execve_error(path, cmd1);
}

void	last_process(char **args, int argc, int perm)
{
	char	**cmd1;
	char	*path;
	int		outfile;

	if (!args[argc -2][0])
	{
		perror("Error");
		close_fds();
		exit(126);
	}
	if (perm == 0)
		outfile = open(args[argc - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		outfile = open(args[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (outfile < 0)
		error();
	cmd1 = ft_split(args[argc - 2], ' ');
	if (!cmd1)
		error();
	path = find_path(cmd1[0]);
	if (args[1]) //1 = write redir flag | check type redir
		redir_input(args[1], args[1]); //1 = write redir flag
	close_fds();
	if (execve(path, cmd1, shell()->env) == -1)
		execve_error(path, cmd1);
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
		temp = ft_strjoin(path[var], "/");
		line = ft_strjoin(temp, cmd);
		free(temp);
		if (access(line, 0) == 0)
			return (ft_free(path), line);
		free(line);
		var++;
	}
	return (ft_free(path), cmd);
}
 */