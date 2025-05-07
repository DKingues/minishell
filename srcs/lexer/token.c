/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:26:54 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/07 13:03:54 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_token *assign_token(char *input)
{
	t_token	*token;
	int 	command;

	command = 0;
	while (*input)
	{
		while(ft_isspace(*input))
			input++;
		if (*input == '|')
			set_token(token, "|", PIPE, &command, &input);
		else if (*input == '<' && *(input + 1) == '<')
			set_token(token, "<<", HERE_DOC, &command, &input);
		else if (*input == '<')
			set_token(token, "<", READ, &command, &input);
		else if (*input == '>' && *input + 1 == '>')
			set_token(token, ">>", APPEND, &command, &input);
		else if (*input == '>')
			set_token(token, ">", TRUNCATE, &command, &input);
		else
		{
			token->value = ft_get_word(*input);
			if (command == 0 && is_command(*input, &command))
				token->type = COMMAND;
			else
				token->type = ARG;
		}
		*input++;
		token = token->next;
	}
	return (token);
}

int		is_command(char *value, int *command)
{
	if (ft_strcmp(value, "echo") || ft_strcmp(value, "cd") || ft_strcmp(value, "pwd") \
	|| ft_strcmp(value, "export") || ft_strcmp(value, "unset") || ft_strcmp(value, "env") \
	|| ft_strcmp(value, "exit"))
	{
		*command = 1;
		return (1);
	}
	return (0);
}

void	set_token(t_token *token, char *value, int type, int *command, char **input)
{
	token->value = ft_strdup(value);
	token->type = type;
	if (ft_strcmp(value, "|"));
		*command = 0;
	if (ft_strcmp(value, "<<") || ft_strcmp(value, ">>"))
		*input++;
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
