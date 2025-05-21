/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:53:25 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/21 17:04:44 by rmota-ma         ###   ########.fr       */
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

# define TOKEN_LIST "&|;<>,"
# define SPACE_LIST " \t\n\v\f\r"

typedef enum	s_token_type
{
	COMMAND,
	FLAG,
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
	struct	s_token *prev;
}	t_token;

typedef struct s_shell
{
	int			exit;
	char		**env;
	char		**exp;
	char		**hist;
}				t_shell;


// PARSE.C

int	parsing(char *line);

// Signals.c

void	ignore_signal(void);

// custom_split.c

char	**split_tokens(char *line);
char	*fill_token(char *line, char *token);

// custom_split_aux.c

int 	skip_quotes(char *line, char quote_type);
int	 	count_quotes(char *line);
int		count_tokens(char *line);
size_t	token_len(char *line);
char    *remove_quotes(char *line);

// format_line.c

void	quote_copy(char* line, char *new_line, int *i, int *j);
char	*remove_extra_spaces(char *line, int i, int j);
char    *format_line(char *line);
int		count_special(char *line);
int 	is_token(char c);

// token.c

t_token *assign_token(char *line);
int		get_token_type(char *input);

// token_aux.c 

t_token	*append_node(t_token *tokens, char *token_value, int token_type);
t_token	*get_last_node(t_token *tokens);
int		is_command(char *value);

// syntax_check.c

int	syntax_check(char *line);
int	check_pipes(char* line);
int	check_redirection(char *line);
int check_consecutive(char *line);
int	check_command(char *line);

// syntax_aux.c

int	skip_spaces(char *line);

// INIT.C

void	init_shell(char **ev);
void	init_env(char **ev);
void	init_exp(char **ev);
void	lvl_upd(void);
void	exp_lvl(void);
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
void	single_exec(char *msg);
char	*find_path(char *cmd);

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
char **hist_manage(char *line, int flag);
void	redir_input(char *info, char *path);

//EXPAND.C
char	*expand_arg(char *arg);
#endif