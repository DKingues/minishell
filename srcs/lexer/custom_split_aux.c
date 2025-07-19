/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:44 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/19 17:48:42 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_quotes(char *line, char quote_type)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != quote_type)
		i++;
	return (i);
}

int	count_quotes(char *line)
{
	int		i;
	int		counter;
	char	temp;

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

int	count_special(char *line)
{
	int	i;
	int	j;
	int	counter;

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

int	cnt_nospc(char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (is_token(line[i]))
		{
			if (line[i - 1] && line[i - 1] != ' ')
				counter++;
			if (line[i + 1] && line[i + 1] != ' ')
				counter++;
		}
		i++;
	}
	return (counter);
}
