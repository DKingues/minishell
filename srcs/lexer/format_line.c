/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:49:28 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/25 16:44:37 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_copy(char *line, char *new_line, int *i, int *j)
{
	char	quote_type;

	quote_type = line[*i];
	new_line[(*j)++] = line[(*i)++];
	while (line[*i] && line[*i] != quote_type)
		new_line[(*j)++] = line[(*i)++];
	if (line[*i] == quote_type)
		new_line[(*j)++] = line[(*i)++];
	if (!ft_isspace(line[*i]))
	{
		while (line[*i] && (line[*i] != '\"' && line[*i] != '\'')
			&& (!ft_isspace(line[*i]) && !is_token(line[*i])))
			new_line[(*j)++] = line[(*i)++];
		if (line[*i] == '\"' || line[*i] == '\'')
			quote_copy(line, new_line, i, j);
	}
}

int	is_token(char c)
{
	int	i;

	i = 0;
	while (TOKEN_LIST[i])
	{
		if (TOKEN_LIST[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_extra_spaces(char *line, int i, int j, int space)
{
	char	*new_line;

	new_line = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if ((line[i] && !ft_isspace(line[i]))
			|| (line[i] == '\"' || line[i] == '\''))
			space = 0;
		if (line[i] == '\"' || line[i] == '\'')
			quote_copy(line, new_line, &i, &j);
		else if (line[i] && !ft_isspace(line[i]))
			new_line[j++] = line[i++];
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
	char	*new_line;

	new_line = ft_calloc(sizeof(char), (ft_strlen(line) + cnt_nospc(line) + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			quote_copy(line, new_line, &i, &j);
		else if ((is_token(line[i]) && line[i + 1] != '\0'))
		{
			if (i > 0 && line[i - 1] && line[i - 1] != ' ')
				new_line[j++] = ' ';
			if ((line[i] == '>' && line[i + 1] && line[i + 1] == '>')
				|| (line[i] == '<' && line[i + 1] && line[i + 1] == '<'))
				new_line[j++] = line[i++];
			new_line[j++] = line[i++];
			if (line[i] && line[i] != ' ')
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i++];
	}
	return (new_line);
}

char	*format_line(char *line)
{
	int		i;
	int		j;
	int		space;
	char	*temp;

	i = 0;
	j = 0;
	space = 1;
	temp = remove_extra_spaces(line, i, j, space);
	if (!temp)
		return (NULL);
	line = create_spaces(temp, i, j);
	return (free(temp), line);
}
