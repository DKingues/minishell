/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:37:46 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/18 13:12:13 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_check(char *line)
{
	if (count_quotes(line) % 2 != 0)
		return (ft_printf(2, RED INV NOCLR ERR_3), 0);
	else if (check_consecutive(line, 0, 0, 0) == 0)
		return (ft_printf(2, RED INV NOCLR ERR_4), 0);
	else if (check_pipes(line, 0) == 0)
		return (0);
	else if (check_redirection(line, 0) == 0)
		return (0);
	return (1);
}

int	check_pipes(char *line, int i)
{
	i += skip_spaces(&line[i]);
	if (line && line[i] == '|')
		return (ft_printf(2, RED INV NOCLR ERR_5), 0);
	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			i += skip_quotes(&line[i], line[i - 1]) + 1;
		}
		else
		{
			if (line[i] == '|' && line[i + 1] == '|')
				return (ft_printf(2, RED INV NOCLR ERR_1), 0);
			else if (line[i] == '|')
			{
				i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '\0')
					return (ft_printf(2, RED INV NOCLR ERR_2), 0);
			}
			i++;
		}
	}
	return (1);
}

int	check_redirection(char *line, int i)
{
	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			i += skip_quotes(&line[i], line[i - 1]) + 1;
		}
		else
		{
			if (line[i] == '>')
			{
				if (!check_redirection2(line, i, '>'))
					return (ft_printf(2, RED INV NOCLR ERR_6), 0);
			}
			if (line[i] == '<')
			{
				if (!check_redirection2(line, i, '<'))
					return (ft_printf(2, RED INV NOCLR ERR_7), 0);
			}
			else
				i++;
		}
	}
	return (1);
}

int	check_redirection2(char *line, int i, char redir_type)
{
	while (line[i] == redir_type)
		i++;
	i += skip_spaces(&line[i]);
	if (line[i] == '\0')
		return (0);
	return (1);
}

int	check_consecutive(char *line, int i, char temp, int consecutive)
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
				while (line[i++] == temp)
					consecutive++;
				i--;
				if ((temp == '>' || temp == '<') && consecutive > 1)
					return (0);
				else if ((temp != '>' && temp != '<') && consecutive > 0)
					return (0);
			}
			else
				i++;
		}
	}
	return (1);
}
