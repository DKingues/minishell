/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:53:25 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/28 17:47:10 by dicosta-         ###   ########.fr       */
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

# define NO_COLOR "\033[0m"
# define RED "\033[1;31m"
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

typedef struct s_tree
{
	t_token_type	type;
	char 			*value;
	struct	s_token	*right;
	struct	s_token *left;
}	t_tree;

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
t_token	*remove_redir(t_token *token);

// token_aux.c 

t_token	*append_node(t_token *tokens, char *token_value, int token_type);
t_token	*get_last_node(t_token *tokens);
int		is_command(char *value);

// syntax_check.c

int		syntax_check(char *line);
int		check_pipes(char* line);
int		check_redirection(char *line);
int 	check_consecutive(char *line);
int		check_command(char *line);

// syntax_aux.c

int	skip_spaces(char *line);

// expand.c

char	*expand_arg(char *arg);

// expader_check_aux.c

int		expand_check(char *line);
int 	in_double_quotes(char *line, int i);
char 	*remove_expasion(char *line);
int		arg_len(char *expansion_name);

// expander_check.c

char 	*expand_caller(char *line);
char	*add_expansion(char *line, char *expansion, int i);
char	*get_expansion(char *line);

// init.c

void	init_shell(char **ev);
void	init_env(char **ev);
void	init_exp(char **ev);
void	lvl_upd(void);
void	exp_lvl(void);
t_shell	*shell(void);

// commands.c

void	echo_cmd(int flag, char *msg);
void	pwd_cmd(void);
void	exp_cmd(int flag, char *msg);
void	unset_cmd(char *msg);
void	env_cmd(void);

// commands2.c

int	exit_cmd(char *msg, int mult_args);
void	cd_cmd(char *path);
void	single_exec(char *msg);
char	*find_path(char *cmd);

// cmd_utils.c

char	**exp_set(char *msg);
char	**env_set(char *msg);
char	**exp_redef(int var2, char *msg);
char	**env_redef(int var2, char *msg);
size_t	exp_len(const char *s);

// cmd_utils2.c

void	exp_organize(void);
void	second_organize(int	var, int var2);
void	switch_str(int var);
char **re_write_exp(char *msg);
char **re_write_env(char *msg);

// cmd_utils3.c

char	*set_blank(char *msg);
char **quoting_set(void);
char	*exp_strdup(const char *s1);
int	error_syntax(char *array);
int	long_check(char *str);

// cmd_utils4.c

void	set_old_path(void);
void old_path_exp(void);
void set_new_path(void);
void new_path_exp(void);
void	mv_home(void);

// cmd_utils5.c

void	mv_old(void);
void	mv_abs(char *path);
char **hist_manage(char *line, int flag);
void	redir_input(char *info, char *path);

#endif