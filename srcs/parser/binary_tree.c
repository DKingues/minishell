/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:08:44 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/17 17:03:18 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_right_node(t_tree *ast, t_token *token)
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

void	set_left_node(t_tree *ast, t_token *token)
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

t_tree	*phantom_node(void)
{
	t_tree	*new;

	new = ft_calloc(sizeof(t_tree), 1);
	if (!new)
		return (NULL);
	new->value = NULL;
	new->type = COMMAND;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

t_tree	*tokens_to_tree(t_token *token, t_token *target, t_tree *ast)
{
	t_token	*temp;

	if (token == NULL || token == target)
		return (NULL);
	temp = find_pipe(token, target);
	if (temp)
	{
		ast = new_node(temp->value, temp->type);
		ast->right = tokens_to_tree(temp->next, NULL, ast->right);
		ast->left = tokens_to_tree(token, temp, ast->right);
	}
	else
		ast = tokens_to_tree2(token, target, ast);
	return (ast);
}

t_tree	*tokens_to_tree2(t_token *token, t_token *target, t_tree *ast)
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
	return (ast);
}
