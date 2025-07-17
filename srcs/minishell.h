/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:53:25 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/17 18:49:05 by dicosta-         ###   ########.fr       */
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
# include <fcntl.h>

# define NO_COLOR "\033[0m"
# define RED "\033[1;31m"
# define TOKEN_LIST "&|;<>,"
# define SPACE_LIST " \t\n\v\f\r"
# define ERR_1 RED"Invalid:"NO_COLOR" unexpected token '|'.\n"
# define ERR_2 RED"Invalid:"NO_COLOR" no command after pipe.\n"
# define ERR_3 RED"Invalid:"NO_COLOR" unclosed quotes.\n"
# define ERR_4 RED"Invalid:"NO_COLOR" unexpected token.\n"
# define ERR_5 RED"Invalid:"NO_COLOR" no command before pipe.\n"
# define ERR_6 RED"Invalid:"NO_COLOR" no file after '>'.\n"
# define ERR_7 RED"Invalid:"NO_COLOR" no file after '<'.\n"


typedef enum s_token_type
{
	ARG,
	COMMAND,
	PIPE,
	READ,
	HERE_DOC,
	TRUNCATE,
	APPEND,
}	t_token_type;

typedef struct s_tree
{
	t_token_type	type;
	char			*value;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	int		*pids;
	char	**alias;
	int		in;
	int		out;
	int		pid;
	int		count;
	int		*docs;
	int		exit;
	int		pipe_count;
	char	**env;
	char	**exp;
	char	**hist;
	t_tree	*tree;
}	t_shell;

typedef enum s_sig_struct
{
	ROOT,
	CHLD,
	HDOC,
	IGNORE,
}	t_sig_struct;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// binary_tree.c

t_tree	*tokens_to_tree(t_token *token, t_token *target, t_tree *ast);
t_tree	*tokens_to_tree2(t_token *token, t_token *target, t_tree *ast);
void	set_left_node(t_tree *ast, t_token *token);
void	set_right_node(t_tree *ast, t_token *token);
t_tree	*phantom_node(void);

// binary_tree_aux.c

int		parsing(char *line);
void	tree_free(t_tree *ast);
t_token	*find_pipe(t_token *token, t_token *target);
int		pipe_counter(t_token *token);
t_tree	*new_node(char *value, int type);

// parse.C

int		parsing(char *line);

// signals.c

void	root_handler(int signal);
void	heredoc_handler(int signal);
void	choose_signal(t_sig_struct level);

// custom_split.c

char	**split_tokens(char *line);
char	*fill_token(char *line, char *token);
char	*delete_quotes(char *line, char *quoted, int start, int end);
char	*remove_quotes(char *line, int i, char *new_line);
size_t	token_len(char *line);

// custom_split_aux.c

int		skip_quotes(char *line, char quote_type);
int		count_quotes(char *line);
int		count_tokens(char *line);
int		count_special(char *line);
int		cnt_nospc(char *line);

// format_line.c

void	quote_copy(char *line, char *new_line, int *i, int *j);
char	*remove_extra_spaces(char *line, int i, int j, int space);
char	*format_line(char *line);
int		is_token(char c);
char	*create_spaces(char *line, int i, int j);

// token.c

t_token	*assign_token(char *line);
int		get_token_type(char *input);
t_token	*remove_redir(t_token *token);

// token_aux.c 

t_token	*append_node(t_token *tokens, char *token_value, int token_type);
t_token	*get_last_node(t_token *tokens);
int		is_command(char *value);

// syntax_check.c

int		syntax_check(char *line);
int		check_pipes(char *line);
int		check_redirection(char *line);
int		check_consecutive(char *line);
int		check_command(char *line);

// syntax_aux.c

int		skip_spaces(char *line);

// expand.c

char	*expand_arg(char *arg);
char	*expand_arg_continue(char *arg, int var, int len, char *temp);

// expander_check_aux.c

int		in_double_quotes(char *line, int i);
char	*remove_expansion(char *line);
int		arg_len(char *expansion_name);
int		expa_len(char *line);

// expander_check.c

int		expand_check(char *line);
char	*expand(char *line, char *key, int start, int end);
char	*expand_caller(char *line);
char	*add_expansion(char *line, char *expansion, int i);
char	*get_expansion(char *line);

// init.c

void	init_shell(char **ev);
void	init_env(char **ev);
void	init_exp(char **ev);
void	lvl_upd(int var);
void	exp_lvl(int var);
t_shell	*shell(void);

// init2.c

char	*find_home(void);
char	*str_redef(char *str, int var, int var2, int except);
char	*copy_no_nl(char *temp);
void	set_alias(int len, int fd);
void	init_alias(void);
void	init_alias2(int fd, char *line, int var, char *home);

// commands.c

void	echo_cmd(int flag, char *msg);
void	pwd_cmd(void);
void	exp_cmd(int flag, char *msg, int var);
void	unset_cmd(char *msg);
void	env_cmd(t_tree *tree);

// commands2.c

void	exit_cmd(t_tree *tree, int code);
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
void	second_organize(int var, int var2);
void	switch_str(int var);
char	**re_write_exp(char *msg);
char	**re_write_env(char *msg);

// cmd_utils3.c

char	*set_blank(char *msg);
char	**quoting_set(void);
char	*exp_strdup(const char *s1);
int		error_syntax(char *array);
int		long_check(char *str);

// cmd_utils4.c

void	set_old_path(void);
void	old_path_exp(void);
void	set_new_path(void);
void	new_path_exp(void);
void	mv_home(void);

// cmd_utils5.c

void	mv_old(void);
void	mv_abs(char *path);
char	**hist_manage(char *line, int flag);
int		redir_input(t_tree	*redir);

// tree.c

void	execute(t_tree	*cmd);
char	**args_join(t_tree	*cmd);
int		waitpids(int var);
void	close_fds(void);

// get_next_line

char	*get_next_line(int fd);
int		ft_linelen_gnl(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	ft_buffer_clean(char *str);

void	free_list(t_token *token);
void	singleton_free(int exit);
int		manage_here_doc(void);
void	nptree_executer(void);
void	tree_executer(void);
int		flag_check(char *flags, char *valid);
char	*find_home(void);

#endif