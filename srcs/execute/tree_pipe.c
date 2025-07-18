/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:24:31 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/18 14:28:04 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_tree *temp, t_tree *temp2, int check, int *fd)
{
	int	check2;

	check2 = 0;
	free(shell()->pids);
	if (check == 1)
		dup2(fd[1], 1);
	if (temp2->type == READ || temp2->type == HERE_DOC
		|| temp2->type == TRUNCATE || temp2->type == APPEND)
		redir_input(temp2);
	while (temp)
	{
		check2 = 1;
		if (temp->type == READ || temp->type == HERE_DOC
			|| temp->type == TRUNCATE || temp->type == APPEND)
			if(redir_input(temp))
				break ;
		check2 = 0;
		temp = temp->left;
	}
	if (temp2 && temp2->value && temp2->type == COMMAND && !check2)
		execute(temp2);
	else if (temp2->left && temp2->left->value
		&& temp2->left->type == COMMAND && !check2)
		execute(temp2->left);
	exit_help();
}

void	tree_executer(void)
{
	int		fd[2];
	int		var;
	int		check;
	int		check2;
	t_tree	*temp;
	t_tree	*temp2;

	var = 0;
	check = 0;
	shell()->pids = ft_calloc(shell()->pipe_count + 2, sizeof(int));
	shell()->count = 0;
	check2 = 0;
	choose_signal(CHLD);
	temp2 = shell()->tree;
	while (temp2)
	{
		if (temp2->type == PIPE)
		{
			if (pipe(fd) == -1)
				return ;
			check = 1;
		}
		temp = temp2->left;
		shell()->pids[var] = fork();
		if (!shell()->pids[var])
			child_process(temp, temp2, check, fd);
		else
		{
			temp = temp2;
			while (temp)
			{
				if (temp->type == HERE_DOC)
					shell()->count++;
				temp = temp->left;
			}
			if (check == 1)
				dup2(fd[0], 0);
		}
		check = 0;
		if ((temp2 && temp2->value && temp2->type == COMMAND)
			|| (temp2->left && temp2->left->value
				&& temp2->left->type == COMMAND))
			var++;
		temp2 = temp2->right;
	}
	singleton_free(1);
	exit(waitpids(var));
}
