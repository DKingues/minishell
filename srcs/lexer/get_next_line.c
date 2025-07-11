/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:26:22 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/11 15:22:11 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_gnl(line, buffer);
		if (!line)
			return (NULL);
		ft_buffer_clean(buffer);
		if (line[ft_linelen_gnl(line) - 1] == '\n')
			return (line);
	}
	return (line);
}

/* int main(void)
{
	int fd;
	char *line;
	int i = 0;

	fd = open("test.txt", O_RDONLY);
	while (i < 7)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
} */