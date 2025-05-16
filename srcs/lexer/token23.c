/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:26:54 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/15 15:47:53 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../minishell.h"

t_token *assign_token(char *input)
{
	t_token	*token;
	int 	cmd;
	int		i;

	token = NULL;
	cmd = 0;
	i = 0;
	while (input[i])
	{
		while(ft_isspace(input[i]))
			i++;
		if (!(special_token(token, input, &cmd, &i)))
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

void	set_token(t_token *token, char *value, int type, int *cmd, int *i)
{
	token->value = ft_strdup(value);
	token->type = type;
	if (!(ft_strcmp(value, "|")))
		*cmd = 0;
	if (!(ft_strcmp(value, "<<"))|| !(ft_strcmp(value, ">>")))
		*i += 1;
}

char	*ft_get_word(const char *str)
{
	size_t	i;
	char	*mal;

	i = 0;
	mal = ft_calloc(sizeof(char), ft_strlen(str));
	if (!mal)
		return (NULL);
	while (str[i] && str[i] != '|' && str[i] != '<' && str[i] != '>' && !(ft_isspace(str[i])))
	{
		mal[i] = str[i];
		i++;
	}
	return (mal);
}

int	special_token(t_token *token, char *input, int *cmd, int *i)
{
	if (input[*i] == '|')
		set_token(token, "|", PIPE, cmd, i);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		set_token(token, "<<", HERE_DOC, cmd, i);
	else if (input[*i] == '<')
		set_token(token, "<", READ, cmd, i);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		set_token(token, ">>", APPEND, cmd, i);
	else if (input[*i] == '>')
		set_token(token, ">", TRUNCATE, cmd, i);
	else
		return (0);
	return (1);
}*/