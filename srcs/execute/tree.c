/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:41:40 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/18 15:16:05 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	nptree_executer(void)
{
	int		pid;
	int	check2;
	t_tree	*temp;
	t_tree	*temp2;

	pid = 0;
	shell()->count = 0;
	temp = shell()->tree->left;
	temp2 = shell()->tree;
	check2 = 0;
	if (temp2 && temp2->value && temp2->type == COMMAND
		&& is_builtin(temp2->value))
	{
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
		if (temp2 && temp2->value && !ft_strncmp(temp2->value,
				"exit", ft_strlen(temp2->value) + 1))
		{
			dup2(shell()->in, 0);
			dup2(shell()->out, 1);
			ft_printf(1, "exit\n");
		}
		else
			shell()->exit = 0;
		if (temp2 && temp2->value && temp2->type == COMMAND && !check2)
			execute(temp2);
		dup2(shell()->in, 0);
		dup2(shell()->out, 1);
		close_fds();
	}
	else
	{
		shell()->pid = fork();
		if (!shell()->pid)
		{
			choose_signal(HDOC);
			shell()->exit = 0;
			pid = fork();
			if (!pid)
			{
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
				if (shell()->env)
					ft_free_split(shell()->env);
				close_fds();
				exit(shell()->exit);
			}
			else
				waitpid(shell()->pid, &shell()->exit, 0);
			singleton_free(1);
			exit(shell()->exit / 256);
		}
		else
		{
			choose_signal(IGNORE);
			waitpid(shell()->pid, &shell()->exit, 0);
			choose_signal(ROOT);
			shell()->exit = shell()->exit / 256;
		}
	}
}
