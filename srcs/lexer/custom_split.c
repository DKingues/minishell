/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:51:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/14 19:41:03 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fill_token(char *line, char *token)
{
	int i;
	int j;
	char temp;
	
	i = 0;
	j = 0;
	token = ft_calloc(sizeof(char), token_len(&line[i]) + 1);
	if (!token)
		return (NULL);
	if (line[i] == '\"' || line[i] == '\'')
	{
		temp = line[i++];
		while (line[i] && line[i] != temp)
			token[j++] = line[i++];
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
	if (count_quotes(line) % 2 != 0)
		ft_putendl_fd("Error: Invalid quotes\n", 2);
	tokens = ft_calloc(sizeof(char*), count_tokens(line) + 1);
	while (i < count_tokens(line))
	{
		tokens[i] = fill_token(&line[j], tokens[i]);
		if (!tokens[i])
			return (ft_free_split(tokens), NULL);
		j += ft_strlen(tokens[i]);
		i++;
	}
	return(tokens);
}