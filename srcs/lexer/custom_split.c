/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:51:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/31 15:51:21 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fill_token(char *line, char *token, int i, int j)
{
	char	quo;

	token = ft_calloc(sizeof(char), token_len(line) + 1);
	if (!token)
		return (NULL);
	while (line[i] && !ft_isspace(line[i]))
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote_copy(line, token, &i, &j);
			return (token);
		}
		if (line[i] && line[i] == '=' && (line[i + 1] == '\"'
				|| line[i + 1] == '\''))
		{
			token[j++] = line[i++];
			quo = line[i];
			token[j++] = line[i++];
			while (line[i] && line[i] != quo)
				token[j++] = line[i++];
		}
		token[j++] = line[i++];
	}
	return (token);
}

char	**split_tokens(char *line)
{
	int		i;
	int		j;
	char	**tokens;

	i = 0;
	j = 0;
	line = format_line(line);
	tokens = ft_calloc(sizeof(char *), count_tokens(line) + 1);
	if (!tokens)
		return (NULL);
	while (i < count_tokens(line))
	{
		j += skip_spaces(&line[j]);
		tokens[i] = fill_token(&line[j], tokens[i], 0, 0);
		if (!tokens[i])
			return (ft_free_split(tokens), NULL);
		j += token_len(tokens[i]);
		if (!tokens[i])
			return (ft_free_split(tokens), NULL);
		i++;
	}
	return (free(line), tokens);
}

char	*delete_quotes(char *line, char *quoted, int start, int end)
{
	char	*new_line;
	char	*str_start;
	char	*str_end;
	char	*temp;

	str_start = proc_ft_substr(line, 0, start);
	temp = ft_strjoin(str_start, quoted);
	str_end = proc_ft_substr(line, end, ft_strlen(line));
	new_line = ft_strjoin(temp, str_end);
	free(str_end);
	free(quoted);
	return (free(line), remove_quotes(new_line, end - 2, NULL));
}

char	*remove_quotes(char *line, int i, char *new_line)
{
	char	quote;
	int		start;

	quote = 0;
	start = -1;
	while (line[i])
	{
		if (quote == 0 && (line[i] == '\"' || line[i] == '\''))
		{
			quote = line[i];
			start = i;
		}
		else if (new_line == NULL && quote != 0 && quote == line[i])
		{
			new_line = proc_ft_substr(line, start + 1, (i - (start + 1)));
			break ;
		}
		i++;
	}
	if (new_line == NULL)
		return (line);
	if (start != -1)
		return (delete_quotes(line, new_line, start, i + 1));
	return (new_line);
}

size_t	token_len(char *line)
{
	int		i;
	char	temp;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			temp = line[i++];
			while (line[i] && line[i] != temp)
				i++;
			if (line[i] == temp)
				i++;
		}
		else
			i++;
	}
	return (i);
}
