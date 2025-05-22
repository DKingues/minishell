/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:17:53 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/22 21:06:15 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expander_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;	
			i += skip_quotes(&line[i], '\'');
		}
		else if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_caller(char *line)
{
	int		i;
	int		j;
	char	*expansion;
	char 	*temp;
	
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;	
			i += skip_quotes(&line[i], '\'');
		}
		else if (line[i] == '$')
		{
			temp = ft_calloc(sizeof(char), expansion_len(&line[i]) + 1);
			if (!temp)
				return (NULL);
			while (line[i] && !ft_isspace(line[i]))
				temp[j++] = line[i++];
			expansion = expand_arg(temp);
		}
		i++;
	}
	if (expansion)
		line = expanded_line(line, expansion);
	return (line);
}


char	*expanded_line(char *line, char *expansion)
{
	int	i;
	char *expanded_line;
	
	i = 0;
	expanded_line = ft_calloc(sizeof(char), (ft_strlen(line) + ft_strlen(expansion)) + 1);
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;	
			i += skip_quotes(&line[i], '\'');
		}
		else if (line[i] == '$')
		{
			line = remove_expasion(&line[i]);
			return (i);
		}	
	}
	return (free(line), expanded_line);
}

int expansion_len(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;	
			i += skip_quotes(&line[i], '\'');
		}
		else if (line[i] == '$')
		{
			while (line[i] && (!ft_isspace(line[i]) && line[i] != '='))
				i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char *remove_expasion(char *line)
{
	int	i;
	int	j;
	char *new_line;

	i = 0;
	j = 0;
	new_line = ft_calloc(sizeof(char), (ft_strlen(line) - expansion_len(line)) + 1);
	while (line[i])
	{
		if (line[i] == '\'')
			quote_copy(line, new_line, &i, &j);
		else if (line[i] == '$')
		{
			while (line[i] && !ft_isspace(line[i]))
				i++;
			i++;
		}
		new_line[j++] = line[i++];
		i++;
	}
	return (new_line);
}
