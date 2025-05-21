/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:02:59 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/21 16:21:44 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*append_node(t_token *tokens, char *token_value, int token_type)
{
	t_token	*node;
	t_token	*last_node;

	node = ft_calloc(sizeof(t_token), 1);
	node->next = NULL;
	node->prev = NULL;
	node->value = token_value;
	node->type = token_type;
	if (!tokens)
		tokens = node;
	else
	{
		last_node = get_last_node(tokens);
		last_node->next = node;
		last_node->next->prev = last_node;
	}
	return (tokens);
}

t_token	*get_last_node(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int		is_command(char *value)
{
	if (!(ft_strcmp(value, "echo")) || !(ft_strcmp(value, "cd")) || !(ft_strcmp(value, "pwd")) \
	|| !(ft_strcmp(value, "export")) || !(ft_strcmp(value, "unset")) || !(ft_strcmp(value, "env")) \
	|| !(ft_strcmp(value, "exit")) || !(ft_strcmp(value, "history")))
		return (1);
	return (0);
}