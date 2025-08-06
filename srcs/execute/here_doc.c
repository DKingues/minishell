/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:08:14 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 19:56:33 by rmota-ma         ###   ########.fr       */
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
			if (temp->type == HD || temp->type == HD2)
				count++;
			temp = temp->left;
		}
		tree = tree->right;
	}
	if (!count)
		return (0);
	shell()->docs = ft_calloc(count + 1, sizeof(int));
	if (!shell()->docs)
		malloc_err(NULL, "malloc");
	return (1);
}

int	loop_docs(int count, t_tree *temp)
{
	int	fd[2];

	if (pipe(fd) == -1)
		malloc_err(NULL, "pipe");
	shell()->pid = fork();
	if (!shell()->pid)
	{
		choose_signal(HDOC);
		close(fd[0]);
		if (temp->type == HD)
			return (here_doc(temp->value, fd[1], NULL, NULL), 0);
		here_doc2(temp->value, fd[1]);
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
			if (temp->type == HD || temp->type == HD2)
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

void	malloc_err(char **incognito, char *msg)
{
	if (incognito)
		ft_free_split(incognito);
	ft_printf(2, "minishell: %s error\nexit\n", msg);
	shell()->exit = 1;
	exit_cmd(NULL, 0);
}

char	*pid_expand(char *temp, char *arg)
{
	temp = ft_strdup(shell()->proc_id);
	if (!temp)
	{
		free(arg);
		malloc_err(NULL, "malloc");
	}
	if (ft_strlen(arg) >= 2)
		temp = ft_strjoin(temp, arg + 2);
	if (!temp)
	{
		free(arg);
		malloc_err(NULL, "malloc");
	}
	return (temp);
}
