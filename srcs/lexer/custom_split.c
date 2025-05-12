/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:51:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/12 14:48:28 by dicosta-         ###   ########.fr       */
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
	token = ft_calloc(sizeof(char), token_len(line) + 1);
	if (line[i] == '\"' || line[i] == '\'')
	{
		temp = line[i];
		i++;
		while (line[i] != temp && line[i] != '\0')
			token[j++] = line[i++];
		return (token);
	}
    while (!ft_isspace(line[i]) && line[i] != '\0')
		token[j++] = line[i++];
	return (token);
}

/*char *allocate_token(char *line, char *token)
{
	int i; 
	
	i = 0;
	token = ft_calloc(sizeof(char), custom_linelen(line) + 1);
	token = fill_token(line, token, i);
	return (token);
}*/

char **split_tokens(char *line)
{
	int		i;
	int		j;
	char	**tokens;

	i = 0;
	j = 0;
	if (count_quotes(line) % 2 != 0)
		return(ft_putendl_fd("Error: Unmatched quotes", 2), NULL);
	tokens = ft_calloc(sizeof(char*), count_tokens(line) + 1);
	if(!tokens)
		return (ft_free_split(tokens), NULL);
	while (i < count_tokens(line))
	{
		while (ft_isspace(line[j]))
		j++;
		tokens[i] = fill_token(&line[j], tokens[i]);
		if(!tokens[i])
			return(ft_free_split(tokens), NULL);
		ft_printf("[%s]\n\n", tokens[i]);
		i++;
	}
	
	return(tokens);
}