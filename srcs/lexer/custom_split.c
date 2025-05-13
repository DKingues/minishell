/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:51:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/13 18:03:47 by dicosta-         ###   ########.fr       */
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
	char **tokens;

	if (count_quotes(line) % 2 != 0)
		ft_putendl_fd("Error: Invalid quotes\n", 2);
	tokens = malloc(sizeof(char*) * count_tokens(line) + 1);
	
	
	return(tokens);
}