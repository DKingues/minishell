/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:57:26 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/06 15:22:01 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *assign_token(char *line)
{
	t_token	*token;
	char 	**tokens;
	int		i;
	int		token_type;
	
	token = NULL;
	tokens = split_tokens(line);
	i = 0;
	while (tokens[i])
	{
		token_type = get_token_type(tokens[i]);
		if (token_type == READ || token_type == HERE_DOC \
		|| token_type == TRUNCATE || token_type == APPEND)
			token = append_node(token, tokens[++i], token_type);
		else
			token = append_node(token, tokens[i], token_type);
		i++;
	}
	return (token);
}
/*t_token	*remove_redir(t_token *token)
{
	t_token	*temp;
	t_token	*next;
	
	temp = token;
	while (temp)
	{
		next = temp->next;
		if (temp->type == READ || temp->type == HERE_DOC \
		|| temp->type == TRUNCATE || temp->type == APPEND)
		{
			temp->next->type = temp->type;
			if (temp->prev)
			{
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
			}
			else
				temp->next->prev = NULL;
			free(temp);
		}
		temp = next;
	}
	return (temp);
}*/
int	get_token_type(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			return(PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
			return(HERE_DOC);
		else if (input[i] == '<')
			return (READ);
		else if (input[i] == '>' && input[i + 1] == '>')
			return (APPEND);
		else if (input[i] == '>')
			return (TRUNCATE);
		else
			return(ARG);
	}
	return (1);
}



