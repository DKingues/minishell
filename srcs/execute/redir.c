/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:06:06 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 19:56:23 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_input2(t_tree *redir, int fd, char *temp)
{
	DIR	*directory;

	if (redir->type == TRUNCATE)
	{
		directory = opendir(redir->value);
		fd = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd > 0 && !directory)
			return (dup2(fd, 1), 0);
	}
	else if (redir->type == APPEND)
	{
		directory = opendir(redir->value);
		fd = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd > 0 && !directory)
			return (dup2(fd, 1), 0);
	}
	if (fd < 0 || directory)
	{
		if (directory)
			closedir(directory);
		return (trunc_help(temp, redir->value));
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
			if (!temp)
				malloc_err(NULL, "malloc");
			perror(temp);
			shell()->exit = 1;
			return (free(temp), 1);
		}
		dup2(fd, 0);
		return (0);
	}
	else if (redir->type == HD || redir->type == HD2)
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
	if (i == 1)
		code = 0;
	free(shell()->pids);
	return (code / 256);
}

void	here_doc2(char *eof, int fd)
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

void	here_doc(char *eof, int fd, char *line, char *temp)
{
	int		len;

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
		temp = ft_strdup(line);
		line = expand_caller(line);
		line = hdoc_exp(line, temp);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		free(temp);
	}
}
