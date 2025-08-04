/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:03:49 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 19:16:20 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mv_old(void)
{
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "OLDPWD=", 7))
		{
			while (shell()->env[var][var2] != '=')
				var2++;
			chdir(shell()->env[var] + var2 + 1);
			set_old_path(0, 0, 0, NULL);
			set_new_path(0, NULL, NULL);
			pwd_cmd();
			return ;
		}
		var++;
	}
	ft_printf(2, "minishell: cd: OLDPWD not set\n");
}

void	mv_abs(char *path)
{
	char	*abs_path;
	char	*temp;

	abs_path = ft_strdup(shell()->safe_home);
	if (!abs_path)
		malloc_err(NULL, "malloc");
	abs_path = ft_strjoin(abs_path, path + 1);
	if (!abs_path)
		malloc_err(NULL, "malloc");
	if (!access(abs_path, 0))
	{
		chdir(abs_path);
		set_old_path(0, 0, 0, NULL);
		set_new_path(0, NULL, NULL);
	}
	else
	{
		temp = ft_nfstrjoin("minishell: ", abs_path);
		if (!temp)
			malloc_err(NULL, "malloc");
		perror(temp);
		free(temp);
		shell()->exit = 1;
	}
	free(abs_path);
}

char	**loop_history(int var, char **temp, char *line)
{
	var = 0;
	while (shell()->hist[var])
	{
		temp[var] = ft_strdup(shell()->hist[var]);
		if (!temp[var])
			return (ft_free_split(temp), NULL);
		var++;
	}
	temp[var] = ft_strdup(line);
	if (!temp[var])
		return (ft_free_split(temp), NULL);
	return (ft_free_split(shell()->hist), temp);
}

char	**hist_manage(char *line, int flag)
{
	char	**temp;
	int		var;

	var = 0;
	if (!line || ((!line[0] || line[0] == '\n') && !flag))
		return (shell()->hist);
	if (flag)
	{
		temp = ft_calloc(sizeof(char *), 2);
		if (temp)
			temp[0] = ft_calloc(sizeof(char *), 2);
		return (ft_free_split(shell()->hist), rl_clear_history(),
			temp);
	}
	add_history(line);
	while (shell()->hist[var])
		var++;
	temp = ft_calloc(sizeof(char *), var + 2);
	if (!temp)
		return (NULL);
	return (loop_history(var, temp, line));
}
