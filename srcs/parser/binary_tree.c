/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:08:04 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/27 18:35:17 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	*add_left(t_tree *tree, char *token_value, int token_type)
{
	t_tree *temp;
	
	temp = ft_calloc(sizeof(t_tree), 1);
	if (!temp)
		return (NULL);
	temp->value = ft_strdup(token_value);
	temp->left = NULL;
	temp->right = NULL;
	temp->type = token_type;
	tree->left = temp;
	return (tree);
}

void	*add_right(t_tree *tree, char *token_value, int token_type)
{
	t_tree *temp;

	temp = ft_calloc(sizeof(t_tree), 1);
	if (!temp)
		return (NULL);
	temp->value = ft_strdup(token_value);
	temp->type = token_type;
	temp->left = NULL;
	temp->right = NULL;
	tree->right = temp;
	return (free(temp), tree);
}

t_tree	tree_head(t_token)
{
	
}
int	organizer(t_token *token)
{
	t_tree	*tree;
	
	while (token)
	{
		if (is_pipe(token))
		{
			add_left(tree, token->value, token->type);
			reset_token(token);
			while (token->type != PIPE && token)
			{
				if (is_redir(token))
			}
		}
	token->next;
	}
}

int	is_pipe(t_token *token)
{
	if (token->type == PIPE)
		return (1);
	return (0);
}
void *reset_token(t_token *token)
{
	while (token)
		token = token->prev;
}
int	*is_redir(t_token *token)
{
	if (token->type == READ || token->type == HERE_DOC \
	|| token->type == TRUNCATE || token->type == APPEND)
		return (1);
	return (0);
}

//PIPE
//REDIR
//ARG