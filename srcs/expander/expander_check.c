/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:44:06 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/04 20:15:42 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quotes(line, i))
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

char	*expand(char *line, char *key, int start, int end)
{
	char	*str_start;
	char	*str_end;
	char	*value;
	char	*new_line;

	value = expand_arg(key);
	str_start = proc_ft_substr(line, 0, start);
	str_end = proc_ft_substr(line, end, ft_strlen(line) - end);
	new_line = ft_strjoin(str_start, value);
	free(value);
	free(key);
	free(line);
	line = ft_strjoin(new_line, str_end);
	free(str_end);
	return (expand_caller(line));
}

char	*expand_caller(char *line)
{
	int		i;
	int		s;
	char	quote;

	s = -1;
	i = 0;
	quote = 0;
	while (line[i])
	{
		if (quote == 0 && (line[i] == '\"' || line[i] == '\''))
			quote = line[i];
		else if (quote == line[i])
			quote = 0;
		if ((quote == 0 || quote == '\"') && (s == -1 && line[i] == '$')
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?'
				|| line[i + 1] == '$'))
			s = i;
		else if ((quote == 0 || quote == '\"') && s != -1
			&& (!ft_isalnum(line[i + 1]) || line[i + 1] == '\0') && ++i)
			break ;
		i++;
	}
	if (s != -1)
		return (expand(line, proc_ft_substr(line, s, (i - s)), s, i));
	return (line);
}

char	*add_expansion(char *line, char *expansion, int i)
{
	int		j;
	int		k;
	int		l;
	int		full_len;
	char	*expanded_line;

	j = 0;
	k = 0;
	l = 0;
	full_len = ft_strlen(line) + ft_strlen(expansion);
	expanded_line = ft_calloc(sizeof(char), full_len + 1);
	if (!expanded_line)
		return (NULL);
	while (j < full_len)
	{
		if (j == i)
		{
			while (expansion[k])
				expanded_line[j++] = expansion[k++];
		}
		expanded_line[j++] = line[l++];
	}
	return (free(line), free(expansion), expanded_line);
}

char	*get_expansion(char *line)
{
	int		var;
	int		var2;
	char	*expansion;

	var = 0;
	var2 = 0;
	while (line[var])
	{
		if (line[var] == '$')
		{
			while (line[var + var2] && !ft_isspace(line[var + var2]))
				var2++;
			expansion = ft_calloc(var2 + 1, sizeof(char));
			var2 = 0;
			while (line[var + var2] && !ft_isspace(line[var + var2]))
			{
				expansion[var2] = line[var + var2];
				var2++;
			}
			return (expansion);
		}
		var++;
	}
	return (NULL);
}
