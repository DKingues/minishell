/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:29:35 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/24 19:30:05 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_token *token)
{
	while (token)
	{
		ft_printf(1, "Value: [%s]\t Type: [%d]\n", token->value, token->type);	
		token = token->next;
	}
}

char *go_back(char *line, char *temp, int var)
{
	int	var2;
	char *res;

	var2 = 0;
	while (temp[var + var2] && temp[var + var2] != line[var + 1])
		var2++;
	res = ft_calloc(ft_strlen(line) + var2 + 1, sizeof(char));
	var2 = 0;
	while(var2 < var)
	{
		res[var2] = line[var2];
		var2++;
	}
	while (temp[var2] && temp[var2] != line[var + 1])
	{
		res[var2] = temp[var2];
		var2++;
	}
	while (temp[var2] && line[var2])
	{
		res[var2] = line[var2];
		var2++;
	}
	return (res);
}

char *rm_noprint(char *line)
{
	char *res;
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	res = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while(line[var + var2])
	{
		if (line[var + var2] && line[var + var2] == '\1')
			var2++;
		if (line[var + var2])
		{
			res[var] = line[var + var2];
			var++;
		}
	}
	return (res);
}

char *hdoc_exp(char *line, char *temp)
{
	int	var;
	char *res;

	var = 0;
	res = NULL;
	while (line[var])
	{
		if(line[var] == '<' && line[var + 1] && line[var + 1] == '<')
		{
			var += 2;
			while(line[var] && ft_isspace(line[var]))
				var++;
			if(line[var] && (line[var] == '\1' || temp[var] == '$'))
				res = go_back(line, temp, var);
		}
		var++;
	}
	if (!res)
		res = rm_noprint(line);
	free(line);
	return (res);
}

int	parser(char *line)
{
	t_token	*token;
	char *temp;

	if (syntax_check(line) == 0)
		return (0);
	temp = ft_strdup(line);
	line = expand_caller(line);
	if (syntax_check2(line) == 0)
		return (free(temp), 0);
	line = hdoc_exp(line, temp);
	token = assign_token(line);
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
		return (free(line), 0);
	else if (check_consecutive2(line, 0, 0) == 0)
		return (free(line), ft_printf(2, "\n"), 0);
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
			i = check_pipes_aux(line, i);
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
