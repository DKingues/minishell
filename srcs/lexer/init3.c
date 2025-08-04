/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:36:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/04 19:19:20 by rmota-ma         ###   ########.fr       */
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
			init_err1(0);
		shell()->alias[0] = ft_strdup("");
		if (!shell()->alias[0])
			init_err1(1);
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
			init_err1(0);
		shell()->alias[0] = ft_strdup("");
		if (!shell()->alias[0])
			init_err1(1);
		return ;
	}
	set_alias(var, fd);
}

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}

void	just_do_it(int var, int var2, int len, char *temp)
{
	free(shell()->env[var]);
	len = ft_strlen(shell()->env[var2]);
	temp = ft_calloc(sizeof(char), len + 5);
	if (!temp)
		malloc_err(NULL, "malloc");
	ft_strcpy(temp, "OLDPWD=");
	ft_strcpy(temp + 7, shell()->env[var2] + 4);
	shell()->env[var] = ft_strdup(temp);
	if (!shell()->env[var])
	{
		free(temp);
		malloc_err(NULL, "malloc");
	}
	free(temp);
}

void	just_do_it_too(int var, int var2, int len, char *temp)
{
	free(shell()->exp[var]);
	len = ft_strlen(shell()->exp[var2]);
	temp = ft_calloc(sizeof(char), len + 5);
	if (!temp)
		malloc_err(NULL, "malloc");
	ft_strcpy(temp, "OLDPWD=");
	ft_strcpy(temp + 7, shell()->exp[var2] + 4);
	shell()->exp[var] = ft_strdup(temp);
	if (!shell()->exp[var])
	{
		free(temp);
		malloc_err(NULL, "malloc");
	}
	free(temp);
}
