/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:17:03 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/02 15:34:56 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
}

int	check_pipes_aux(char *line, int i)
{
	i++;
	i += skip_quotes(&line[i], line[i - 1]);
	if (line[i])
		i++;
	return (i);
}

int	check_pipes_rev(char *line, int i)
{
	while (i > 0 && ft_isspace(line[i]))
		i--;
	if (line[i] == '|')
		return (ft_printf(2, RED INV NOCLR ERR_2), 0);
	return (1);
}

int	check_spaces(char *expansion)
{
	int	var;

	var = 0;
	if (!expansion && !expansion[0])
		return (0);
	while (expansion[var])
	{
		if (ft_isspace(expansion[var]))
			return (0);
		var++;
	}
	return (1);
}

int	check_redir_exp(char *line, int v, int v2, int check2)
{
	int		check;

	v = 0;
	check2 = 1;
	while (line[v])
	{
		v2 = 0;
		check = 0;
		if (line[v] == '<' || line[v] == '>')
		{
			if (line[v] == '<' && line[v + 1] == '<')
				v++;
			else
				if (!check_redir_next(&v, v2, line, check))
					return (0);
		}
		v++;
	}
	return (check2);
}
