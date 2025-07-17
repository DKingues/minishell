/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:57:26 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/15 15:49:44 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dequote_tokens(t_token **token)
{
	if (!token || !*token)
		return ;
	while ((*token)->next)
	{
		if (count_quotes((*token)->value) % 2 == 0)
			(*token)->value = remove_quotes((*token)->value, 0, NULL);
		(*token) = (*token)->next;
	}
	if (count_quotes((*token)->value) % 2 == 0)
		(*token)->value = remove_quotes((*token)->value, 0, NULL);
	while ((*token)->prev)
		(*token) = (*token)->prev;
}

t_token	*assign_token(char *line)
{
	t_token	*token;
	char	**tokens;
	int		i;
	int		token_type;

	token = NULL;
	tokens = split_tokens(line);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != 0)
		{
			token_type = get_token_type(tokens[i]);
			if ((token_type == READ || token_type == HERE_DOC
					|| token_type == TRUNCATE || token_type == APPEND)
				&& get_token_type(tokens[i + 1]) != PIPE)
				token = append_node(token, tokens[++i], token_type);
			else
				token = append_node(token, tokens[i], token_type);
		}
		i++;
	}
	dequote_tokens(&token);
	ft_free_split(tokens);
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
		if (temp->type == READ || temp->type == HERE_DOC
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
			return (PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (HERE_DOC);
		else if (input[i] == '<')
			return (READ);
		else if (input[i] == '>' && input[i + 1] == '>')
			return (APPEND);
		else if (input[i] == '>')
			return (TRUNCATE);
		else
			return (ARG);
	}
	return (1);
}
