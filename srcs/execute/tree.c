/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:41:40 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/06/05 20:45:50 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tree_executer(void)
{
	//int	fd[2];
	//int var = 0;
	//int	*pids;
	t_tree *temp;
	
	//pids = ft_calloc(shell()->pipe_count + 2, sizeof(int));
	while(shell()->tree)
	{
		if(shell()->tree->type == PIPE)
			ft_printf(2, "PIPING\n");
			/* if (pipe(fd) == -1)
				return ; */
		temp = shell()->tree->left;
		/* pids[var] = fork();
		if(!pids[var])
		{ */
		while(temp)
		{
			if(temp->type == COMMAND)
				ft_printf(2, "EXECUTING\n");
			else if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
				ft_printf(2, "REDIRECTING\n");
			temp = temp->left;
		}
		if(shell()->tree->type == READ || shell()->tree->type == HERE_DOC || shell()->tree->type == TRUNCATE || shell()->tree->type == APPEND)
			ft_printf(2, "REDIRECTING\n");
		else if(shell()->tree->type == COMMAND)
			ft_printf(2, "EXECUTING\n");
			//exit(0);
		/*}
		else if (shell()->tree->type == PIPE && pids[var])
			dup2(fd[0], 0);
		var++; */
		shell()->tree = shell()->tree->right;
	}
}