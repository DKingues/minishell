/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:37:46 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/11 16:12:54 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_check(char *line)
{
	if (count_quotes(line) % 2 != 0)
		return (ft_printf(2, RED"Invalid:"NO_COLOR" unclosed quotes.\n"), 0);
	/*else if (check_command(line) == 0)
		return (ft_putendl_fd("Invalid: unknown command.", 2), 0);*/
	else if (check_pipes(line) == 0)
		return (0);
	else if (check_consecutive(line) == 0)
		return (ft_printf(2, RED"Invalid:"NO_COLOR" unexpected token.\n"), 0);
	else if (check_redirection(line) == 0)
		return (0);
	/*else if (check_null(line) == 0)
		return (ft_putendl_fd("Invalid: no command.", 2), 0);
	else if (check_heredoc(line) == 0)
		return (ft_putendl_fd("Invalid: no EOF.", 2), 0);*/
	return (1);
}
int	check_pipes(char* line)
{
	int		i;
	
	i = 0;
	i += skip_spaces(&line[i]);
	if(line && line[i] == '|')
		return (ft_printf(2, RED"Invalid:"NO_COLOR" no command before pipe.\n"), 0); // echo "||"
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
				return (ft_printf(2, RED"Invalid:"NO_COLOR" unexpected token \'|\'.\n"), 0);
			else if (line[i] == '|')
			{
				i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '\0')
					return (ft_printf(2, RED"Invalid:"NO_COLOR" no command after pipe.\n"), 0);
			}
			i++;
		}
	}
	return (1);
}

int	check_redirection(char *line)
{
	int	i;
	
	i = 0;
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
				while (line[i] == '>')
					i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '\0')
					return (ft_printf(2, RED"Invalid:"NO_COLOR" no file after \'>\'.\n"), 0);
			}
			if (line[i] == '<')
			{
				while (line[i] == '<')
					i++;
				i += skip_spaces(&line[i]);
				if (line[i] == '\0')
					return (ft_printf(2, RED"Invalid:"NO_COLOR" no file after \'<\'.\n"), 0);
			}
			else
				i++;
		}
	}
	return (1);
}

int check_consecutive(char *line)
{
	char	temp;
	int		i;
	int		consecutive;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			i += skip_quotes(&line[i], line[i - 1]) + 1;
		}
		else
		{	
			consecutive = 0;
			if (is_token(line[i]))
			{
				temp = line[i++];
				while (line[i] == temp)
				{
					i++;
					consecutive++;
				}
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

/*int	check_command(char *line)
{
	int		i;
	int		j;
	char	*first_word;

	i = 0;
	j = 0;
	first_word = ft_calloc(sizeof(char), token_len(line) + 1);
	if (!first_word)
		return (free(first_word), 0);
	i += skip_spaces(line);
	while (line[i] && !ft_isspace(line[i]))
		first_word[j++] = line[i++];
	if (is_token(first_word[0]) && first_word[0] != '|')
		return (free(first_word), 1);
	else if (is_command(first_word))
		return (free(first_word), 1);
	return (free(first_word), 0);
}*/
