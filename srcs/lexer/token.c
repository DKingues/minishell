/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:26:54 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/06 18:37:45 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_token *tokenizer(char *input)
{
	t_token	*token;
	int command;

	command = 0;
	while (*input)
	{
		while(ft_isspace(*input))
			input++;
		if (*input == '|')
		{
			token->value = '|';
			token->type = PIPE;
			command = 0;
		}
		else if (*input == '<' && *input + 1 == '<')
		{
			token->value = '<<';
			token->type = HERE_DOC;
			*input++;
		}
		else if (*input == '<')
		{
			token->value = '<';
			token->type = READ;
		} 
		else if (*input == '>' && *input + 1 == '>')
		{
			token->value = '>>';
			token->type = APPEND;
			*input++;
		}
		else if (*input == '>')
		{
			token->value = '>';
			token->type = TRUNCATE;
		} 
		else
		{
			token->value = ft_get_word(*input);
			if (command == 0 && (token->value == 'cd' ||token->value == 'echo' ||token->value == 'ls' ||token->value == 'pwd'))
			{
				token->type = COMMAND;
				command = 1;
			}
			else
				token->type = ARG;
		}
		*input++;
		token = token->next;
	}
	return (token);
}

char	*ft_get_word(const char *str)
{
	size_t	i;
	size_t	j;
	char	*mal;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '|' && str[j] != '<' && str[j] != '>' && !(ft_isspace(str[j])))
		j++;
	mal = ft_calloc(sizeof(char), j + 1);
	if (!mal)
		return (NULL);
	while (str[i] && str[i] != '|' && str[i] != '<' && str[i] != '>' && !(ft_isspace(str[i])))
	{
		mal[i] = str[i];
		i++;
	}
	return (mal);
}