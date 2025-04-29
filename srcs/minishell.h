/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:53:25 by dicosta-          #+#    #+#             */
/*   Updated: 2025/04/29 15:59:59 by rmota-ma         ###   ########.fr       */
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
//# include <curses.h>				// tgetent, tgetflag, tgetnum, tgetstr ...
# include <readline/readline.h>
# include <readline/history.h>

//PARSE.C
void	parsing(void);

#endif