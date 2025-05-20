/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:57:26 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/20 17:27:25 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *assign_token(char *line)
{
	t_token	*token;
	char 	**tokens;
	int		i;
	int		token_type;
	int		command;
	
	token = NULL;
	tokens = split_tokens(line);
	i = 0;
	command = 0;
	while (tokens[i])
	{
		token_type = get_token_type(tokens[i]);
		token = append_node(token, tokens[i], token_type);
		if (token_type == COMMAND && command == 0)
			command = 1;
		if (token_type == PIPE && command == 1)
			command = 0;
		i++;
	}
	return (token);
}

int	get_token_type(char *input)
{
	int	i;

	i = 0;
	if (is_command(input))
		return (COMMAND);
	//if (is_flag(input))
	//	return (FLAG);
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
			return (ARG);
	}
	return (1);
}

