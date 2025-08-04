/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:35:02 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 19:26:11 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_malandro(char *line, int *v)
{
	char	*temp22;

	shell()->exit = 1;
	temp22 = get_expansion(line + (*v));
	if (!temp22)
		return (singleton_free(1), free(line), exit(1), 0);
	ft_printf(2, "%s: ambiguous redirect\n",
		temp22);
	if (temp22)
		free(temp22);
	while (line[(*v)])
	{
		if (line[(*v)] == '|')
			break ;
		(*v)++;
		if (!line[(*v) + 1])
			return (0);
	}
	return (1);
}

int	seilamare(int *v, int v2, char *line, int check)
{
	(*v)++;
	while (line[(*v)] && ft_isspace(line[(*v)]))
		(*v)++;
	if (line[(*v)] == '$' && line[(*v) + 1]
		&& !ft_isspace(line[(*v) + 1]) && line[(*v) + 1] != '?')
	{
		while (shell()->env[v2])
		{
			if (!ft_strncmp(shell()->env[v2],
					line + (*v) + 1, exp_len(shell()->env[v2])))
				check = check_spaces(shell()->env[v2]);
			v2++;
		}
		if (!check)
			if (!check_malandro(line, v))
				return (0);
	}
	return (1);
}

void	singleton_free_docs(int exit)
{
	if (exit)
	{
		ft_free_split(shell()->env);
		close_fds();
	}
	ft_free_split(shell()->alias);
	ft_free_split(shell()->hist);
	ft_free_split(shell()->exp);
	if (shell()->tree)
		tree_free(shell()->tree);
	if (shell()->proc_id)
		free(shell()->proc_id);
	if (shell()->safe_home)
		free(shell()->safe_home);
}
