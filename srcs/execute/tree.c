/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:41:40 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/06/06 17:42:38 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**args_join(t_tree	*cmd)
{
	int	var;
	char	**res;
	t_tree	*temp;
	
	var = 0;
	temp = cmd;
	while(temp)
	{
		var++;
		temp = temp->right;
	}
	res = ft_calloc(sizeof(char *), var + 1);
	var = 0;
	while(cmd)
	{
		res[var] = ft_strdup(cmd->value);
		cmd = cmd->right;
		var++;
	}
	return(res);
}

void	execute(t_tree	*cmd)
{
	char	*path;
	char **args;

	path = find_path(cmd->value);
	if(!path)
		perror("");
	args = args_join(cmd);
	close_fds();
	if(execve(path, args, shell()->env) == -1)
		perror("");
	exit(0);
}

int	redir_input(t_tree	*redir)
{
	int	fd;
	
	if(redir->type == READ)
	{
		fd = open(redir->value, O_RDONLY);
		dup2(fd, 0);
		return (0);
	}
	else if(redir->type == HERE_DOC)
	{
		printf("HERE_DOC");
		return (0);
	}
	else if (redir->type == TRUNCATE)
	{
		fd = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, 1);
		return (0);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, 1);
		return (0);
	}
	return(1);
}

int	waitpids(int *pids, int var)
{
	int	code;
	
	code = 0;
	var--;
	while(var >= 0)
	{
		waitpid(pids[var], &code, 0);
		var--;
	}
	free(pids);
	return (code / 256);
}

void	close_fds(void)
{
	int	var;

	var = 3;
	while (var < 1024)
	{
		close(var);
		var++;
	}
}

void	tree_executer(void)
{
	int	fd[2];
	int var = 0;
	int	*pids;
	int	check;
	t_tree *temp;
	
	check = 0;
	pids = ft_calloc(shell()->pipe_count + 2, sizeof(int));
	while(shell()->tree)
	{
		if(shell()->tree->type == PIPE)
		{
			if (pipe(fd) == -1)
				return ;
			check = 1;
		}
		temp = shell()->tree->left;
		pids[var] = fork();
		if(!pids[var])
		{
			if(check == 1)
			{
				dup2(fd[1], 1);
				close(fd[0]);
			}
			while(temp)
			{
				if(temp->type == COMMAND)
					execute(temp);
				else if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
					redir_input(temp);
				temp = temp->left;
			}
			if(shell()->tree->type == READ || shell()->tree->type == HERE_DOC || shell()->tree->type == TRUNCATE || shell()->tree->type == APPEND)
				redir_input(shell()->tree);
			else if(shell()->tree->type == COMMAND && shell()->tree->value)
				execute(shell()->tree);
		}
		else if (check == 1)
		{
			dup2(fd[0], 0);
			close(fd[1]);
			close (0);
		}
		var++;
		check = 0;
		shell()->tree = shell()->tree->right;
	}
	shell()->exit = waitpids(pids, var);
}
