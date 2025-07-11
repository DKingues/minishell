/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:51:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/25 12:06:21 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fill_token(char *line, char *token)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	token = ft_calloc(sizeof(char), token_len(line) + 1);
	if (!token)
		return (NULL);
	if (line[i] == '\"' || line[i] == '\'')
	{
		quote_copy(line, token, &i, &j);
		return (token);
	}
    while (line[i] && !ft_isspace(line[i]))
		token[j++] = line[i++];
	return (token);
}

char **split_tokens(char *line)
{
	int		i;
	int		j;
	char	**tokens;
	
	i = 0;
	j = 0;
	line = format_line(line);
	tokens = ft_calloc(sizeof(char*), count_tokens(line) + 1);
	while (i < count_tokens(line))
	{
		j += skip_spaces(&line[j]);
		tokens[i] = fill_token(&line[j], tokens[i]);
		if (!tokens[i])
			return (ft_free_split(tokens), NULL);
		j += token_len(tokens[i]);
		if(!tokens[i])
			return (ft_free_split(tokens), NULL);
		i++;
	}
	return(free(line), tokens);
}
