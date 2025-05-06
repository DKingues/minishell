/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:53:25 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/06 18:05:12 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/libft.h"
# include <stdio.h>					// printf, perror
# include <stdlib.h>				// malloc, free, exit, getenv
# include <unistd.h>				// write, read, access, open, close ...
# include <sys/wait.h>				// wait, waitpid, wait3, wait4
# include <signal.h>				// signal, sigaction, sigemptyset, sigaddset
# include <sys/stat.h>				// stat, lstat, fstat
# include <dirent.h>				// opendir, readdir, closedir
# include <string.h>				// strerror
# include <sys/ioctl.h>				// ioctl
# include <termios.h>				// tcsetattr, tcgetattr
# include <curses.h>				// tgetent, tgetflag, tgetnum, tgetstr ...
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	s_token_type
{
	COMMAND,
	ARG,
	PIPE,		// |
	READ,		// <
	HERE_DOC, 	// <<
	TRUNCATE,	// >
	APPEND,		// >>
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char 			*value;
	struct	t_token			*next;
}	t_token;

typedef struct s_shell
{
	int		exit;
	char	**env;
}				t_shell;

// PARSE.C

int	parsing(char *line);

// INIT.C

void init_shell(char **ev);
void	init_env(char **ev);
t_shell	*shell(void);

// PIPE.C

// Commands.c

// Token.c

t_token tokenizer(char *input);
t_token	*token(void);

void	ignore_shell_signal(void);


#endif