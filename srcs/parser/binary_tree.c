/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:26:56 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/28 20:46:25 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Direction 1 = Right
// Direction -1 = Left
// Direction 0 = Neutral;
t_tree	*create_branch(t_tree *tree, char *value, int type, int direction)
{
	t_tree	*new;
	t_tree	*right_node;
	t_tree	*left_node;
	
	new = ft_calloc(sizeof(t_tree), 1);
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->right = NULL;
	new->left = NULL;
	if (!tree)
		tree = new;
	if (tree && direction == 1)
	{
		right_node = get_right_node(tree);
		right_node->right = new;
	}
	if (tree && direction == -1)
	{
		left_node = get_left_node(tree);
		left_node->left = new;
	}
	return (tree);
}

t_tree	*get_right_node(t_tree *tree)
{
	t_tree	*temp;
	
	if (!tree)
		return (NULL);
	temp = tree;
	while (temp->right)
		temp = temp->right;
	return (temp);
}
t_tree	*get_left_node(t_tree *tree)
{
	t_tree	*temp;
	
	if (!tree)
		return (NULL);
	temp = tree;
	while (temp->left)
		temp = temp->left;
	return (temp);
}

t_tree	*tree_organizer(t_token	*token)
{
	t_tree	*tree;
	t_token	*temp;
	
	tree = NULL;
	
	while (token)
	{
		if (token->type == PIPE)
		{
			tree = create_branch(tree, token->value, token->type, 0);
			temp = get_nodes_before_pipe(token);
			while (temp && temp->type != PIPE)
			{
				if (token->type == READ || token->type == HERE_DOC \
				|| token->type == TRUNCATE || token->type == APPEND)
					tree = create_branch(tree, token->value, token->type, -1);
				temp = temp->next;
			}
		}
		else if (token->type == READ || token->type == HERE_DOC \
		|| token->type == TRUNCATE || token->type == APPEND)
		{
			
		}
		token = token->next;
	}
}

t_token		*get_nodes_before_pipe(t_token *token)
{
	while (token->prev != NULL && token->prev->type != PIPE)
		token = token->prev;
	return (token);
}

//PIPE
//REDIR
//ARG