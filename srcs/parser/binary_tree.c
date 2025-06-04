/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:08:44 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/04 17:55:16 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void set_right_node(t_tree *ast, t_token *token)
{
	while (ast)
	{
		if (ast->right == NULL)
		{
			ast->right = new_node(token->value, token->type);
			return ;	
		}
		ast = ast->right;
	}
}

void set_left_node(t_tree *ast, t_token *token)
{
	while (ast)
	{
		if (ast->left == NULL)
		{
			ast->left = new_node(token->value, token->type);
			return ;	
		}
		ast = ast->left;
	}
	
}
t_tree	*new_node(char *value, int type)
{
	t_tree	*new;
	
	new = ft_calloc(sizeof(t_tree), 1);
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

t_tree	*phantom_node(void)
{
	t_tree	*new;
	
	new = ft_calloc(sizeof(t_tree), 1);
	if (!new)
		return (NULL);
	new->value = NULL;
	new->type = ARG;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

t_tree	*tokens_to_tree(t_token *token, t_token *target, t_tree *ast, int depth)
{
	t_token	*temp;
	
	if (token == NULL || token == target)
		return (NULL);
	temp = find_pipe(token, target);
	if (temp)
	{
		ast = new_node(temp->value, temp->type);
		ast->right = tokens_to_tree(temp->next, NULL, ast->right, depth + 1);
		ast->left = tokens_to_tree(token, temp, ast->right, depth + 1);
	}
	else
	{
		ast = phantom_node();
		while (!(token == NULL || token == target))
		{
			if (token->type != ARG)
				set_left_node(ast, token);
			else
			{
				if (ast->value == NULL)
					ast->value = ft_strdup(token->value);
				else	
					set_right_node(ast, token);
			}
			token = token->next;
		}
	}
	return (ast);
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
t_token *find_pipe(t_token *token, t_token *target)
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

int pipe_counter(t_token *token)
{
	int	pipes;

	pipes = 0;
	while (token->next)
	{
		if (token->type == PIPE)
			pipes++;
		token = token->next;
	}
	return (pipes);
}
