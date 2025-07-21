/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:17:03 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/21 18:38:31 by rmota-ma         ###   ########.fr       */
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

int	redir_exp_helper(char **line, int *var, int *var2, int *check)
{
	while (shell()->env[(*var2)])
	{
		if (!ft_strncmp(shell()->env[(*var2)],
				(*line) + (*var) + 1, exp_len(shell()->env[(*var2)])))
			(*check)++;
		(*var2)++;
	}
	if (!(*check))
	{
		shell()->exit = 1;
		ft_printf(2, "%s: ambiguous redirect\n",
			get_expansion((*line) + (*var)));
		while ((*line)[(*var)])
		{
			if ((*line)[(*var)] == '|')
				break ;
			var++;
			if (!(*line)[(*var) + 1])
				return (1);
		}
	}
	return (0);
}

int	check_redir_exp(char *line, int v, int v2, int check2)
{
	int	check;

	while (line[v])
	{
		v2 = 0;
		check = 0;
		if (line[v] == '<' || line[v] == '>')
		{
			if (line[v] == '<' && line[v + 1] == '<')
				v++;
			else
			{
				v++;
				while (line[v] && ft_isspace(line[v]))
					v++;
				if (line[v] == '$' && line[v + 1]
					&& !ft_isspace(line[v + 1]) && line[v + 1] != '?')
					check2 = redir_exp_helper(&line, &v, &v2, &check);
				if (check2)
					return (0);
			}
		}
		v++;
	}
	return (check2);
}
