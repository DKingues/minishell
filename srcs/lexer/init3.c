/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:36:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/26 15:03:51 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_alias(void)
{
	int		fd;
	char	*line;
	int		var;
	char	*home;

	var = 0;
	home = find_home_alias();
	home = ft_strjoin(home, "/.zshrc");
	if (!home)
		return ;
	fd = open(home, O_RDONLY);
	line = NULL;
	if (fd == -1)
	{
		if (home)
			free(home);
		shell()->alias = ft_calloc(1, sizeof(char *));
		if (!shell()->alias)
		{
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
		shell()->alias[0] = ft_strdup("");
		if (!shell()->alias[0])
		{
			if (shell()->alias)
				ft_free_split(shell()->alias);
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
		return ;
	}
	init_alias2(fd, line, var, home);
}

void	init_alias2(int fd, char *line, int var, char *home)
{
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp("alias ", line, 6))
			var++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	fd = open(home, O_RDONLY);
	free(home);
	if (fd == -1)
	{
		shell()->alias = ft_calloc(1, sizeof(char *));
		if (!shell()->alias)
		{
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
		shell()->alias[0] = ft_strdup("");
		if (!shell()->alias[0])
		{
			if (shell()->alias)
				ft_free_split(shell()->alias);
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
		return ;
	}
	set_alias(var, fd);
}

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}
