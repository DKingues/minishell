/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:24:31 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 17:53:28 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_help2(int check2)
{
	if (check2)
		singleton_free(1);
	else if (shell()->env)
		ft_free_split(shell()->env);
	exit(shell()->exit);
}

void	exit_help_child(int check2)
{
	if (!check2)
	{
		singleton_free(0);
		close_fds();
	}
	exit_help2(check2);
}

void	child_process(t_tree *temp, t_tree *temp2, int check, int *fd)
{
	int	check2;

	check2 = 0;
	free(shell()->pids);
	if (check == 1)
		dup2(fd[1], 1);
	while (temp)
	{
		check2 = 1;
		if (temp->type == READ || temp->type == HD || temp->type == HD2
			|| temp->type == TRUNCATE || temp->type == APPEND)
			if (redir_input(temp))
				break ;
		check2 = 0;
		temp = temp->left;
	}
	if (temp2 && temp2->value && temp2->type == COMMAND && !check2)
		execute(temp2, NULL, NULL);
	else if (temp2->left && temp2->left->value
		&& temp2->left->type == COMMAND && !check2)
		execute(temp2->left, NULL, NULL);
	else
		exit_help_child(check2);
	exit_help2(check2);
}

int	parent_process(t_tree *temp2, int *check, int *fd, int var)
{
	t_tree	*temp;

	temp = temp2;
	while (temp)
	{
		if (temp->type == HD || temp->type == HD2)
			shell()->count++;
		temp = temp->left;
	}
	if (*check == 1)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if ((temp2 && temp2->value && temp2->type == COMMAND)
		|| (temp2->left && temp2->left->value
			&& temp2->left->type == COMMAND))
		var++;
	*check = 0;
	return (var);
}

void	tree_executer(int var, int check, t_tree *temp, t_tree *temp2)
{
	int		fd[2];

	shell()->pids = ft_calloc(shell()->pipe_count + 2, sizeof(int));
	if (!shell()->pids)
		malloc_err(NULL, "malloc");
	shell()->count = 0;
	choose_signal(CHLD);
	temp2 = shell()->tree;
	while (temp2)
	{
		if (temp2->type == PIPE)
		{
			if (pipe(fd) == -1)
				malloc_err(NULL, "pipe");
			check = 1;
		}
		temp = temp2->left;
		shell()->pids[var] = fork();
		if (!shell()->pids[var])
			child_process(temp, temp2, check, fd);
		else
			var = parent_process(temp2, &check, fd, var);
		temp2 = temp2->right;
	}
	exit(waitpids(var));
}
