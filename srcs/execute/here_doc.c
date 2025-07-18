/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:08:14 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/18 14:23:38 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_docs(void)
{
	t_tree	*tree;
	t_tree	*temp;
	int		count;

	count = 0;
	tree = shell()->tree;
	while (tree)
	{
		temp = tree;
		while (temp)
		{
			if (temp->type == HERE_DOC)
				count++;
			temp = temp->left;
		}
		tree = tree->right;
	}
	if (!count)
		return (0);
	shell()->docs = ft_calloc(count + 1, sizeof(int));
	return (1);
}

int	loop_docs(int count, t_tree *temp)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit(0);
	shell()->pid = fork();
	if (!shell()->pid)
	{
		choose_signal(HDOC);
		close(fd[0]);
		here_doc(temp->value, fd[1]);
	}
	else
	{
		choose_signal(IGNORE);
		close(fd[1]);
		waitpid(shell()->pid, &shell()->exit, 0);
		choose_signal(ROOT);
	}
	shell()->exit = shell()->exit / 256;
	if (shell()->exit == 130)
		return (0);
	shell()->docs[count] = fd[0];
	return (1);
}

int	manage_here_doc(void)
{
	t_tree	*tree;
	t_tree	*temp;
	int		count;

	count = 0;
	if (!check_docs())
		return (0);
	tree = shell()->tree;
	while (tree)
	{
		temp = tree;
		while (temp)
		{
			if (temp->type == HERE_DOC)
			{
				if (!loop_docs(count, temp))
					return (1);
				count++;
			}
			temp = temp->left;
		}
		tree = tree->right;
	}
	return (0);
}
