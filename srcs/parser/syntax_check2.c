/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:29:35 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/04 20:16:12 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*redef_token_value(char *value)
{
	int		var;
	char	*res;

	var = 0;
	res = ft_calloc(sizeof(char), ft_strlen(value) + 1);
	if (!res)
		malloc_err(NULL, "malloc");
	while (value[var])
	{
		if (value[var] == '\2')
			res[var] = '\'';
		else if (value[var] == '\3')
			res[var] = '\"';
		else
			res[var] = value[var];
		var++;
	}
	return (free(value), res);
}

t_token	*redef_token(t_token *token)
{
	while (token && token->next)
	{
		if (token->value)
			token->value = redef_token_value(token->value);
		token = token->next;
	}
	if (token && token->value)
		token->value = redef_token_value(token->value);
	while (token && token->prev)
		token = token->prev;
	return (token);
}

int	parser(char *line)
{
	t_token	*token;
	char	*temp;

	if (syntax_check(line) == 0)
		return (0);
	temp = ft_strdup(line);
	if (!temp)
		return (singleton_free(1), free(line), exit(1), 0);
	line = expand_caller(line);
	if (syntax_check2(line) == 0)
		return (free(temp), 0);
	line = hdoc_exp(line, temp);
	token = assign_token(line);
	token = redef_token(token);
	if (token)
	{
		pipe_counter(token);
		shell()->tree = tokens_to_tree(token, NULL, shell()->tree);
	}
	free_list(token);
	free(line);
	free(temp);
	return (1);
}

int	syntax_check2(char *line)
{
	if (check_pipes2(line, 0) == 0)
	{
		shell()->exit = 2;
		return (free(line), 0);
	}
	else if (check_consecutive2(line, 0, 0) == 0)
	{
		shell()->exit = 2;
		return (free(line), ft_printf(2, "\n"), 0);
	}
	return (1);
}

int	check_redirection2(char *line, int i, char *exp)
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
					return (ft_printf(2, "%s: "AMB, exp), free(exp), 0);
			}
			else
				i++;
		}
	}
	return (1);
}
