/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:17:03 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 12:22:37 by rmota-ma         ###   ########.fr       */
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
	if(!expansion && !expansion[0])
		return (0);
	while(expansion[var])
	{
		if (ft_isspace(expansion[var]))
			return (0);
		var++;
	}
	return (1);
}

int	check_redir_exp(char *line, int v, int v2, int check2)
{
	int	check;

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
			{
				v++;
				while (line[v] && ft_isspace(line[v]))
					v++;
				if (line[v] == '$' && line[v + 1]
					&& !ft_isspace(line[v + 1]) && line[v + 1] != '?')
				{
					while (shell()->env[v2])
					{
						if (!ft_strncmp(shell()->env[v2],
							line + v + 1, exp_len(shell()->env[v2])))
							check = check_spaces(shell()->env[v2]);
						v2++;
					}
					if (!check)
					{
						shell()->exit = 1;
						char *temp22 = get_expansion(line + v);
						if (!temp22)
							return (singleton_free(1), free(line), exit(1), 0);
						ft_printf(2, "%s: ambiguous redirect\n",
							temp22);
						if(temp22)
							free(temp22);
						while (line[v])
						{
							if (line[v] == '|')
								break ;
							v++;
							if (!line[v + 1])
								return (0);
						}
					}
				}
			}
		}
		v++;
	}
	return (check2);
}
