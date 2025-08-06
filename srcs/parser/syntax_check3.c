/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:50:25 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/02 15:20:45 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_checkerer(char *line)
{
	if (check_redirection(line, 0) == 0)
	{
		shell()->exit = 2;
		return (free(line), 0);
	}
	else if (!check_redir_exp(line, 0, 0, 1))
	{
		shell()->exit = 1;
		return (free(line), 0);
	}
	return (1);
}

void	go_go_back(char *res, char *temp, char *line)
{
	free(res);
	free(temp);
	free(line);
	shell()->exit = 1;
	exit_cmd(NULL, 0);
}

char	*go_back(char *line, char *temp, int var, int var2)
{
	char	*res;

	var2 = 0;
	while (temp[var + var2] && temp[var + var2] != line[var + 1])
		var2++;
	res = ft_calloc(ft_strlen(line) + var2 + 1, sizeof(char));
	if (!res)
		go_go_back(res, temp, line);
	var2 = 0;
	while (var2 < var)
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

char	*rm_noprint(char *line, char *temp)
{
	char	*res;
	int		var;
	int		var2;

	var = 0;
	var2 = 0;
	res = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!res)
	{
		free(temp);
		free(line);
		shell()->exit = 1;
		exit_cmd(NULL, 0);
	}
	while (line[var + var2])
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

char	*noprint_pt2(char *line, char *temp, char *lol)
{
	char	*res;
	int		var;
	int		var2;

	var = 0;
	var2 = 0;
	res = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!res)
	{
		free(line);
		shell()->exit = 1;
		return (free(lol), free(temp), exit_cmd(NULL, 0), NULL);
	}
	while (line[var + var2])
	{
		if (line[var + var2] == '$' && line[var + var2 + 1])
		{
			if ((line[var + var2 + 1] == '\'' || line[var + var2 + 1] == '\"')
				&& count_quotes(line + var) % 2 == 0)
				var2++;
		}
		res[var] = line[var + var2];
		var++;
	}
	return (free(line), res);
}
