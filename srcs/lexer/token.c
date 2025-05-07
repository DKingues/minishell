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

#include "../minishell.h"

t_token *assign_token(char *input)
{
	t_token	*token;
	int 	cmd;
	int		i;

	token = malloc(sizeof(t_token));
	if(!token)
		return (NULL);
	cmd = 0;
	i = 0;
	while (input[i])
	{
		while(ft_isspace(input[i]))
			i++;
		if (input[i] == '|')
			set_token(token, "|", PIPE, &cmd, &i);
		else if (input[i] == '<' && input[i + 1] == '<')
			set_token(token, "<<", HERE_DOC, &cmd, &i);
		else if (input[i] == '<')
			set_token(token, "<", READ, &cmd, &i);
		else if (input[i] == '>' && input[i + 1] == '>')
			set_token(token, ">>", APPEND, &cmd, &i);
		else if (input[i] == '>')
			set_token(token, ">", TRUNCATE, &cmd, &i);
		else
		{
			token->value = ft_get_word(&input[i], &i);
			if (cmd == 0 && is_command(token->value, &cmd))
				token->type = COMMAND;
			else
				token->type = ARG;
		}
		i++;
		ft_printf("TYPE: [%d]\t VALUE: [%s]\n", token->type, token->value);
	}
	return (token);
}

int		is_command(char *value, int *cmd)
{
	if (ft_strcmp(value, "echo") || ft_strcmp(value, "cd") || ft_strcmp(value, "pwd") \
	|| ft_strcmp(value, "export") || ft_strcmp(value, "unset") || ft_strcmp(value, "env") \
	|| ft_strcmp(value, "exit"))
	{
		*cmd = 1;
		return (1);
	}
	return (0);
}

void	set_token(t_token *token, char *value, int type, int *cmd, int *i)
{
	token->value = ft_strdup(value);
	token->type = type;
	if (ft_strcmp(value, "|"))
		*cmd = 0;
	if (ft_strcmp(value, "<<") || ft_strcmp(value, ">>"))
		*i += 1;
}

char	*ft_get_word(const char *str, int *i)
{
	size_t	k;
	size_t	j;
	char	*mal;

	k = 0;
	j = 0;
	while (str[j] && str[j] != '|' && str[j] != '<' && str[j] != '>' && !(ft_isspace(str[j])))
		j++;
	mal = ft_calloc(sizeof(char), j + 1);
	if (!mal)
		return (NULL);
	while (str[k] && str[k] != '|' && str[k] != '<' && str[k] != '>' && !(ft_isspace(str[k])))
	{
		mal[k] = str[k];
		k++;
	}
	*i += k;
	return (mal);
}
