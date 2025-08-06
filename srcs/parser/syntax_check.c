/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:37:46 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/02 15:20:25 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_check(char *line)
{
	if (count_quotes(line) % 2 != 0)
	{
		shell()->exit = 2;
		return (free(line), ft_printf(2, RED INV NOCLR ERR_3), 0);
	}
	else if (check_pipes(line, skip_spaces(line)) == 0)
	{
		shell()->exit = 2;
		return (free(line), 0);
	}
	else if (!check_pipes_rev(line, ft_strlen(line) - 1))
	{
		shell()->exit = 2;
		return (free(line), 0);
	}
	else if (check_consecutive(line, 0, 0) == 0)
	{
		shell()->exit = 2;
		return (free(line), ft_printf(2, RED INV NOCLR ERR_4), 0);
	}
	else
		return (syntax_checkerer(line));
	return (1);
}

int	check_pipes(char *line, int i)
{
	if (line && line[i] == '|')
		return (ft_printf(2, RED INV NOCLR ERR_5), 0);
	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_pipes_aux(line, i);
		else
		{
			if (line[i] == '|' && line[i + 1] == '|')
				return (ft_printf(2, RED INV NOCLR ERR_1), 0);
			else if (line[i] == '|')
			{
				i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '|')
					return (ft_printf(2, RED INV NOCLR ERR_1), 0);
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
	char	rd;

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
				rd = line[i];
				while (line[i] == rd)
					i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '\0' || line[i] == '|')
					return (ft_printf(2, RED INV NOCLR ERR_6" '%c'.\n", rd), 0);
			}
			else
				i++;
		}
	}
	return (1);
}

int	check_consecutive(char *line, int i, char temp)
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
				if ((temp == '>' || temp == '<')
					&& consec_counter(&i, line, temp) > 1)
					return (0);
				else if ((temp != '>' && temp != '<')
					&& consec_counter(&i, line, temp) > 0)
					return (0);
			}
			else
				i++;
		}
	}
	return (1);
}

int	consec_counter(int *i, char *line, char temp)
{
	int	consecutive;

	consecutive = 0;
	while (line[*i] && line[*i] == temp)
	{
		(*i)++;
		consecutive++;
	}
	return (consecutive);
}
