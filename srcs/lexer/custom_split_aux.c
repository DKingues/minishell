/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:44 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/15 11:05:13 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int skip_quotes(char *line, char quote_type)
{
    int i;

    i = 0;
    while (line[i] && line[i] != quote_type)
        i++;
    return (i);
}

int count_quotes(char *line)
{
    int i;
    int counter;
    char temp;

    i = 0;
    counter = 0;
    while (line[i])
    {
        if (line[i] == '\"' || line[i] == '\'' )
        {
            temp = line[i];
            i++;
            counter++;
            i += skip_quotes(&line[i], temp);
            if (line[i] == temp)
            {
                counter++;
                i++;
            }
        }
        else  
            i++;
    }
    return (counter);
}

int	count_tokens(char *line)
{
	int i;
	int counter;
	char quote_type;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote_type = line[i++];
			i += skip_quotes(&line[i], quote_type);
		}
		if (ft_isspace(line[i]) || line[i + 1] == '\0')
		{
			while (ft_isspace(line[i + 1]))
				i++;
			counter++;
		}
		i++;
	}
	return (counter);
}

char    *remove_quotes(char *line)
{
    int     i;
    int     j;
    char    *new_line;

    i = 0;
    j = 0;
    new_line = ft_calloc(sizeof(char), token_len(line) - 1);
    if (!new_line)
        return (NULL);
    while (line[i])
    {
        if (line[i] == '\"' || line[i] == '\'')
            i++;
        new_line[j++] = line[i++];
    }
    return (new_line);
}

size_t  token_len(char *line)
{
    size_t i;
    char temp;
    
    i = 0;
    if (line[i] == '\"' || line[i] == '\'')
	{
		temp = line[i++];
		while (line[i] && line[i] != temp)
			i++;
        if (line[i] == temp)
			i++;
        return(i);
	}
    while (line[i] && !ft_isspace(line[i]))
        i++;
    return(i);
}
