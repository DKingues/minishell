/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:01:51 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 20:14:03 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*normie_expander(char *temp, int var, int len, char *arg)
{
	char	*res;

	temp = ft_strdup(shell()->exp[var] + len + 1);
	if (!temp)
		return (free(arg), malloc_err(NULL, "malloc"), NULL);
	temp = ft_strjoin(temp, arg + len + 1);
	if (!temp)
		return (free(arg), malloc_err(NULL, "malloc"), NULL);
	res = ft_calloc(ft_strlen(temp), sizeof(char));
	var = 0;
	while (temp[var + 2])
	{
		if (temp[var + 1] == '\'')
			res[var] = '\2';
		else if (temp[var + 1] == '\"')
			res[var] = '\3';
		else
			res[var] = temp[var + 1];
		var++;
	}
	return (free(temp), res);
}

void	close_fds(void)
{
	int	var;

	var = 3;
	while (var < 1024)
	{
		close(var);
		var++;
	}
}

char	*hdoc_exp(char *line, char *temp)
{
	int		var;
	char	*res;

	var = 0;
	res = NULL;
	while (line[var])
	{
		if (line[var] == '<' && line[var + 1] && line[var + 1] == '<')
		{
			var += 2;
			while (line[var] && ft_isspace(line[var]))
				var++;
			if (line[var] && (line[var] == '\1' || temp[var] == '$'))
				res = go_back(line, temp, var, 0);
		}
		var++;
	}
	if (!res)
	{
		res = rm_noprint(line, temp);
		res = noprint_pt2(res, temp, line);
	}
	free(line);
	return (res);
}
