/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:53:25 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/10 18:33:13 by dicosta-         ###   ########.fr       */
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
# include <limits.h>

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
	struct	s_token	*next;
}	t_token;

typedef struct s_shell
{
	int		exit;
	char	**env;
	char	**exp;
}				t_shell;


// PARSE.C

int	parsing(char *line);

// INIT.C

void	init_shell(char **ev);
void	init_env(char **ev);
void	init_exp(char **ev);
t_shell	*shell(void);

// COMMANDS.C
void	echo_cmd(int flag, char *msg);
void	pwd_cmd(void);
void	exp_cmd(int flag, char *msg);
void	unset_cmd(char *msg);
void	env_cmd(void);

// COMMANDS2.C
int	exit_cmd(char *msg, int mult_args);
void	cd_cmd(char *path);

// CMD_UTILS.C
char	**exp_set(char *msg);
char	**env_set(char *msg);
char	**exp_redef(int var2, char *msg);
char	**env_redef(int var2, char *msg);
size_t	exp_len(const char *s);

// CMD_UTILS2.C
void	exp_organize(void);
void	second_organize(int	var, int var2);
void	switch_str(int var);
char **re_write_exp(char *msg);
char **re_write_env(char *msg);

// CMD_UTILS3.C
char	*set_blank(char *msg);
char **quoting_set(void);
char	*exp_strdup(const char *s1);
int	error_syntax(char *array);
int	long_check(char *str);

// CMD_UTILS4.C
void	set_old_path(void);
void old_path_exp(void);
void set_new_path(void);
void new_path_exp(void);
void	mv_home(void);

// CMD_UTILS5.C
void	mv_old(void);
void	mv_abs(char *path);

// Signals.c

void	ignore_shell_signal(void);

// qtd_split.c

int ft_buffed_split(char *str);
int	ft_count_words(char *str);

// qtd_split_aux.c

int quote_counter(char *str);
int skip_quotes(char *str, char quote_type);

// Token.c

t_token *assign_token(char *input);
int		is_command(char *value, int *cmd);
void	set_token(t_token *token, char *value, int type, int *command, int *i);
char	*ft_get_word(const char *str, int *i);
int		special_token(t_token *token, char *input, int *cmd, int *i);

#endif