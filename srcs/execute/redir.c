/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:06:06 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/19 11:55:24 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_input2(t_tree *redir, int fd, char *temp)
{
	if (redir->type == TRUNCATE)
	{
		fd = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
		{
			temp = ft_nfstrjoin("minishell: ", redir->value);
			perror(temp);
			free(temp);
			shell()->exit = 1;
			return (1);
		}
		return (dup2(fd, 1), 0);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
		{
			temp = ft_nfstrjoin("minishell: ", redir->value);
			perror(temp);
			free(temp);
			shell()->exit = 1;
			return (1);
		}
		return (dup2(fd, 1), 0);
	}
	return (1);
}

int	redir_input(t_tree	*redir)
{
	int		fd;
	char	*temp;

	if (redir->type == READ)
	{
		fd = open(redir->value, O_RDONLY);
		if (fd < 0)
		{
			temp = ft_nfstrjoin("minishell: ", redir->value);
			perror(temp);
			free(temp);
			shell()->exit = 1;
			return (1);
		}
		dup2(fd, 0);
		return (0);
	}
	else if (redir->type == HERE_DOC)
	{
		dup2(shell()->docs[shell()->count], 0);
		shell()->count++;
		return (0);
	}
	return (redir_input2(redir, 0, NULL));
}

int	waitpids(int var)
{
	int	code;
	int	i;

	i = 0;
	code = 0;
	singleton_free(1);
	close(0);
	while (i < var)
	{
		waitpid(shell()->pids[i], &code, 0);
		i++;
	}
	free(shell()->pids);
	return (code / 256);
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

void	here_doc(char *eof, int fd)
{
	int		len;
	char	*line;

	len = ft_strlen(eof);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strncmp(eof, line, len + 1))
		{
			if (line)
				free(line);
			else
				ft_printf(2, "minishell: warning: here-document at line 1\
					delimited by end-of-file (wanted `%s')\n", eof);
			singleton_free(1);
			close_fds();
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
