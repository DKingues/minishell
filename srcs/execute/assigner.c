/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:02:32 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/30 12:38:01 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign(t_tree *tree)
{
	int	fd[2];
	t_tree	*temp;
	int	pid;
	
	while(tree)
	{
		temp = tree;
		while(temp)
		{
			if(temp->type == PIPE)
			{
				if(pipe(fd) == -1)
					return ;
			}
			else
			{
				pid = fork();
				if(pid == 0)
				{
					if(temp->type == COMMAND)
						single_exec();
					else
					{
						while(temp->type == HERE_DOC || temp->type == APPEND || temp->type == TRUNCATE || temp->type == READ)
						{
							redir_input();
							temp = temp->left
						}
						if(temp && temp->type == COMMAND)
							single_exec();
						else if(temp->right && temp->right->type == COMMAND)
							single_exec();
					}
				}
				else
					dup2(fd[0], 0);
			}
			if(temp)
				temp = temp->left;
		}
		tree = tree->right;
	}
}
