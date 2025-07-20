/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:29:35 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/20 20:14:18 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_check2(char *line)
{
	if (!ft_strcmp(line, "\"\"") || !ft_strcmp(line, "\'\'"))
	{
		shell()->parser = 1;
		shell()->exit = 127;
		return (free(line), ft_printf(2, "\n"), 0);
	}
	else if (check_pipes2(line, 0) == 0)
		return (free(line), 0);
	else if (check_consecutive2(line, 0, 0) == 0)
		return (free(line), ft_printf(2, "\n"), 0);
	else if (check_redirection2(line, 0) == 0)
		return (free(line), 0);
	return (1);
}

int	check_pipes2(char *line, int i)
{
	i += skip_spaces(&line[i]);
	if (line && line[i] == '|')
		return (0);
	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			i += skip_quotes(&line[i], line[i - 1]);
			if (line[i])
				i++;
		}
		else
		{
			if (line[i] == '|' && line[i + 1] == '|')
				return (0);
			else if (line[i] == '|')
			{
				i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '\0')
					return (0);
			}
			i++;
		}
	}
	return (1);
}

int	check_redirection2(char *line, int i)
{
	char	redir_type;

	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			i += skip_quotes(&line[i], line[i - 1]) + 1;
		}
		else
		{
			if (line[i] == '>' || line[i] == '<')
			{
				redir_type = line[i];
				while (line[i] == redir_type)
					i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '\0' || line[i] == '|')
					return (0);
			}
			else
				i++;
		}
	}
	return (1);
}

int	check_consecutive2(char *line, int i, char temp)
{
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			i += skip_quotes(&line[i], line[i - 1]) + 1;
		}
		else
		{
			if (is_token(line[i]))
			{
				temp = line[i++];
				if ((temp == '>' || temp == '<') && consec_counter(&i, line, temp) > 1)
					return (0);
				else if ((temp != '>' && temp != '<') &&  consec_counter(&i, line, temp) > 0)
					return (0);
			}
			else
				i++;
		}
	}
	return (1);
}

