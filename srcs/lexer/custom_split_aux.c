/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:44 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/26 18:19:06 by dicosta-         ###   ########.fr       */
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
	int		i;
	int		counter;
	char	quote_type;

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

char    *delete_quotes(char *line, char *quoted, int start, int end)
{
    char *new_line;
    char *str_start;
    char *str_end;
    char *temp;

    str_start = ft_substr(line, 0, start); //echo hello
    temp = ft_strjoin(str_start, quoted); //echo helloworld
    str_end = ft_substr(line, end, ft_strlen(line)); // asdasd
    new_line = ft_strjoin(temp, str_end); //echo helloworld asdasd
    free(str_end);
    free(quoted);
    return (free(line), remove_quotes(new_line, end - 2, NULL));
}
char    *remove_quotes(char *line, int i, char *new_line)
{
    char quote;
    int start;
    
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
            new_line = ft_substr(line, start + 1, (i - (start + 1)));
            break;
        }
        i++;
    }
    if (new_line == NULL)
        return (line);
    if (start != -1)
        return(delete_quotes(line, new_line, start, i + 1));
    return (new_line);
}

size_t  token_len(char *line)
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
    return(i);
}

