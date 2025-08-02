/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_errs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:07:54 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/02 16:26:39 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_err1(int check)
{
	if (check == 1)
	{
		if (shell()->alias)
			ft_free_split(shell()->alias);
	}
	if (shell()->env)
		ft_free_split(shell()->env);
	if (shell()->exp)
		ft_free_split(shell()->exp);
	exit(1);
}

void	init_err2(char *temp)
{
	if (temp)
		free(temp);
	if (shell()->alias)
		ft_free_split(shell()->alias);
	if (shell()->env)
		ft_free_split(shell()->env);
	if (shell()->exp)
		ft_free_split(shell()->exp);
	exit(1);
}

void	init_err3(char *temp, char *temp3)
{
	if (temp)
		free(temp);
	if (temp3)
		free(temp3);
	if (shell()->alias)
		ft_free_split(shell()->alias);
	if (shell()->env)
		ft_free_split(shell()->env);
	if (shell()->exp)
		ft_free_split(shell()->exp);
	exit(1);
}

void	set_alias3(char *line, char *temp, int var, int *len)
{
	char	*temp2;
	char	*temp3;

	temp2 = ft_calloc(sizeof(char), var + 2);
	if (!temp2)
		init_err2(temp);
	var = 0;
	while (line[var + 6] != '=')
	{
		temp2[var] = line[var + 6];
		var++;
	}
	temp2[var] = '=';
	temp3 = ft_strjoin(temp2, temp);
	if (!temp3)
		init_err2(temp);
	shell()->alias[*len] = ft_strdup(temp3);
	if (!shell()->alias[*len])
		init_err3(temp, temp3);
	free(temp3);
	(*len)++;
	free(temp);
}

void	set_alias2(char *line, int *len, int var, char *temp)
{
	temp = str_redef(line + exp_len(line) + 1, 0, 1, 0);
	if (!temp)
		init_err1(1);
	if (temp[ft_strlen(temp) - 1] == '\n')
	{
		temp = copy_no_nl(temp);
		if (!temp)
		{
			if (shell()->alias)
				ft_free_split(shell()->alias);
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
	}
	while (line[var] != '=')
		var++;
	set_alias3(line, temp, var, len);
}
