/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:44:28 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/15 15:43:54 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(char *line)
{
	if (syntax_check(line) == 0)
		return (0);
	return (1);
}

void	tree_free(t_tree *ast)
{
	if (!ast)
		return ;
	tree_free(ast->left);
	tree_free(ast->right);
	if (ast->value)
		free(ast->value);
	free(ast);
}

/*int	add_nodes_to_ast(t_token *token, t_tree **root, int in_pipe)
{
	t_token *curr_pipe;
	t_tree	*ast_node;
	
	curr_pipe = NULL;
	ast_node = NULL;
	if (in_pipe == 0)
		curr_pipe = find_pipe(token);
	if (curr_pipe && curr_pipe->type == PIPE)
	{
		ast_node = new_node(curr_pipe->value, curr_pipe->type);
		
	}
}*/
t_token	*find_pipe(t_token *token, t_token *target)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp == target)
			return (NULL);
		if (temp->type == PIPE)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	pipe_counter(t_token *token)
{
	int	pipes;

	pipes = 0;
	while (token->next)
	{
		if (token->type == PIPE)
			pipes++;
		token = token->next;
	}
	shell()->pipe_count = pipes;
	return (pipes);
}
