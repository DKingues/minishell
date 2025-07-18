/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:36:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/18 15:46:58 by rmota-ma         ###   ########.fr       */
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
	home = find_home();
	home = ft_strjoin(home, "/.zshrc");
	fd = open(home, O_RDONLY);
	line = NULL;
	if (fd == -1)
	{
		if (home)
			free(home);
		shell()->alias = ft_calloc(1, sizeof(char *));
		shell()->alias[0] = ft_strdup("");
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
	fd = open(home, O_RDONLY);
	free(home);
	free(line);
	set_alias(var, fd);
}
