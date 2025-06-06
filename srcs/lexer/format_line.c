/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:49:28 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/06 20:07:20 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_copy(char* line, char *new_line, int *i, int *j)
{
	char quote_type;

	quote_type = line[*i];
	new_line[(*j)++] = line[(*i)++];
	while (line[*i] && line[*i] != quote_type)
		new_line[(*j)++] = line[(*i)++];
	if (line[*i] == quote_type)
		new_line[(*j)++] = line[(*i)++];
	if (!ft_isspace(line[*i]))
	{
		while (line[*i] && (line[*i] != '\"' && line[*i] != '\'') && !ft_isspace(line[*i]))
			new_line[(*j)++] = line[(*i)++];
		if (line[*i] == '\"' || line[*i] == '\'')
			quote_copy(line, new_line, i, j);
	}
}

int count_special(char *line)
{
	int i;
	int j;
	int counter;
	
	i = 0;
	counter = 0;
	while (line[i])
	{
		j = 0;
		while (TOKEN_LIST[j])
		{
			if (TOKEN_LIST[j] == line[i])
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}

int is_token(char c)
{
	int i;

	i = 0;
	while(TOKEN_LIST[i])
	{
		if (TOKEN_LIST[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_extra_spaces(char *line, int i, int j)
{
	int space;
	char *new_line;

	space = 1;
	new_line = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!new_line)
		return (free(new_line), NULL);
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote_copy(line, new_line, &i, &j);
			space = 0;
		}
		else if (line[i] && !ft_isspace(line[i]))
		{
			new_line[j++] = line[i++];
			space = 0;
		}
		else
		{
			if (space == 0)
			{
				new_line[j++] = ' ';
				space = 1;
			}
			i++;
		}
	}
	return (new_line);
}

char	*create_spaces(char *line, int i, int j)
{
	char *new_line;

	new_line = ft_calloc(sizeof(char), (ft_strlen(line) + cnt_nospc(line)) + 1);
	if (!new_line)
		return (free(new_line), NULL);
	while(line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			quote_copy(line, new_line, &i, &j);
		else if (is_token(line[i]) && (line[i + 1] != ' ' && line[i + 1] != '\0'))
		{
			if (line[i - 1] != ' ')
				new_line[j++] = ' ';
			else if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
				new_line[j++] = line[i++];
			new_line[j++] = line[i++];
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i++];
	}
	return(new_line);
}

char    *format_line(char *line)
{
	int		i;
	int		j;
	char	*temp;
	
	i = 0;
	j = 0;
	temp = remove_extra_spaces(line, i, j);
	if (!temp)
		return (NULL);
	line = create_spaces(temp, i, j);
	return (free(temp),line);
}

int cnt_nospc(char *line)
{
	int	i;
	int	counter;
	
	i = 0;
	counter = 0;
	while (line[i])
	{
		if (is_token(line[i]))
		{
			if (line[i - 1] != ' ')
				counter++;
			if (line[i + 1 != ' '])
				counter++;
		}
		i++;
	}
	return (counter);
}