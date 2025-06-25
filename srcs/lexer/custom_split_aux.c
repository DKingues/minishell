/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:44 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/25 20:37:59 by dicosta-         ###   ########.fr       */
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

/*char    *remove_quotes(char *line)
{
    char *new_line;
    size_t  i;

    i = 0;
    new_line = ft_delcpy(line, line[i]);
    return (free(line), new_line);
}*/


/*char    *delete_quotes(char *line, int start, int end)
{
    char *new_line;
    char *str_start;
    char *str_end;
    
    
}*/

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
            start = i + 1;
        }
        else if (new_line == NULL && quote != 0 && quote == line[i])
        {
            new_line = ft_substr(line, start, (i - start));
            break;
        }
        else if (quote != 0 && quote == line[i])
        {
            new_line = ft_strjoin(new_line, ft_substr(line, start, (i - start)));
            break;
        }
        i++;
    }
    if (start != -1)
        return(remove_quotes(line, ++i, new_line));
    return (free(line), new_line);
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

