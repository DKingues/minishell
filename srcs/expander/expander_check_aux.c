/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_check_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:08:26 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/18 13:08:39 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_double_quotes(char *line, int i)
{
	int	j;
	int	quote_end;
	int	quote_start;

	j = i;
	quote_end = 0;
	quote_start = 0;
	while (line[i] && line[i] != '\"')
	{
		i++;
		if (line[i] == '\"')
			quote_end = 1;
	}
	while (j >= 0 && line[j] != '\"')
	{
		j--;
		if (line[j] == '\"')
			quote_start = 1;
	}
	if (quote_start && quote_end)
		return (1);
	return (0);
}

int	arg_len(char *expansion_name)
{
	int	i;

	i = 0;
	while (expansion_name[i] && !ft_isspace(expansion_name[i]))
		i++;
	return (i);
}

char	*remove_expansion(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = ft_calloc(sizeof(char), (ft_strlen(line) - expa_len(line)) + 1);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quotes(&line[i], i))
			quote_copy(line, new_line, &i, &j);
		if (line[i] == '$')
		{
			while (line[i] && !ft_isspace(line[i]))
				i++;
		}
		else
			new_line[j++] = line[i++];
	}
	return (free(line), new_line);
}

int	expa_len(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	while (line[i] && ft_isalnum(line[i]))
	{
		j++;
		i++;
	}
	return (j);
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}
