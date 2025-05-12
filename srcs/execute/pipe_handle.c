/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorpot <scorpot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:11:32 by scorpot           #+#    #+#             */
/*   Updated: 2025/05/12 11:28:45 by scorpot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		redir_input(args[1]); //1 = write redir flag
	else
		dup2(fd[1], 1);
	if (args[0]) //0 = read redir flag | check type redir
		redir_input(args[0]); //0 = read redir flag
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
	path = ft_split(shell()->env[var] + 5, ':', 0, 0);
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

