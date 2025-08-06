/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:53:25 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/04 19:26:21 by rmota-ma         ###   ########.fr       */
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

# define NOCLR "\033[0m"
# define RED "\033[1;31m"
# define TOKEN_LIST "&|;<>,"
# define SPACE_LIST " \t\n\v\f\r"
# define INV "Invalid: "
# define ERR_1 "unexpected token '|'.\n"
# define ERR_2 "no command after pipe.\n"
# define ERR_3 "unclosed quotes.\n"
# define ERR_4 "unexpected token.\n"
# define ERR_5 "no command before pipe.\n"
# define ERR_6 "no file after"
# define AMB "ambiguous redirect."
# define E1 "minishell: warning: shell level"
# define E2 " (%d) too high, resetting to 1\n"

typedef enum s_token_type
{
	ARG,
	COMMAND,
	PIPE,
	READ,
	HD,
	HD2,
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

void	print_tokens(t_token *token);

typedef struct s_shell
{
	char	*safe_home;
	char	*proc_id;
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

//tree.c

void	nptree_executer(t_tree *temp, t_tree *temp2, int pid);
void	nptree_builtin(t_tree *temp, t_tree *temp2, int check2);
void	npchild_process(t_tree *temp, t_tree *temp2, int check2);
void	npparent_process(void);

//tree_pipe.c

int		parent_process(t_tree *temp2, int *check, int *fd, int var);
void	child_process(t_tree *temp, t_tree *temp2, int check, int *fd);
void	tree_executer(int var, int check, t_tree *temp, t_tree *temp2);
void	exit_help2(int check2);

//here_doc.c

char	*pid_expand(char *temp, char *arg);
int		check_docs(void);
int		loop_docs(int count, t_tree *temp);
int		manage_here_doc(void);
void	malloc_err(char **incognito, char *msg);

//redir.c

int		redir_input(t_tree	*redir);
int		redir_input2(t_tree *redir, int fd, char *temp);
void	here_doc(char *eof, int fd, char *line, char *temp);
void	here_doc2(char *eof, int fd);
int		waitpids(int var);

//builtins.c

int		is_builtin(char *cmd);
void	exp_parser(t_tree *temp);
void	echo_parser(t_tree *temp, int flag, char *str);
void	cd_parser(t_tree *temp);
void	history_parser2(t_tree *temp, int flag, int var);

//builtins2.c

void	history_parser(t_tree *temp, int flag);
void	builtin_exec2(t_tree *temp);
void	builtin_exec(t_tree *tree);
int		check_loop(char *path);
char	*str_loop(t_tree *temp, char *str);

//helper.c

int		flag_check(char *flags, char *valid);
char	**args_join(t_tree	*cmd, int var);
char	*search_alias(char *path);
char	**split_redef(char **args, t_tree *cmd);
char	**split_redef2(t_tree *temp2, char **temp, char **args, int var);

//helper2.c

char	*normie_expander(char *temp, int var, int len, char *arg);
void	close_fds(void);
char	*hdoc_exp(char *line, char *temp);

//process.c

void	execute(t_tree	*cmd, char *temp, char *path);
char	**args_except(t_tree *cmd, char *path, char *temp);
char	*path_check(t_tree *cmd);
void	execute2(char *temp, char *path, char **args, char *cmd);
void	exec_err(char *path, char *temp);

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

// signals.c

void	root_handler(int signal);
void	heredoc_handler(int signal);
void	choose_signal(t_sig_struct level);

// custom_split.c

char	**split_tokens(char *line);
char	*fill_token(char *line, char *token, int i, int j);
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
void	else_exec(char *path);

// token_aux.c 

t_token	*append_node(t_token *tokens, char *token_value, int token_type);
t_token	*get_last_node(t_token *tokens);
int		is_command(char *value);

// syntax_check.c

int		syntax_check(char *line);
int		check_pipes(char *line, int i);
int		check_redirection(char *line, int i);
int		check_consecutive(char *line, int i, char temp);
int		consec_counter(int *i, char *line, char temp);

// syntax_check2.c

int		parser(char *line);
void	free_list(t_token *token);
int		syntax_check2(char *line);

// syntax_check3.c

int		syntax_checkerer(char *line);
char	*rm_noprint(char *line, char *temp);
char	*go_back(char *line, char *temp, int var, int var2);
void	go_go_back(char *res, char *temp, char *line);
char	*noprint_pt2(char *line, char *temp, char *lol);

// syntax_check4.c

int		final_check(char *line, int *v);
int		check_redir_next(int *v, int v2, char *line, int check);
void	singleton_free_docs(int exit);
int		check_pipes2(char *line, int i);
int		check_consecutive2(char *line, int i, char temp);

// syntax_check_aux.c

int		check_pipes_aux(char *line, int i);
int		check_pipes_rev(char *line, int i);
int		check_redir_exp(char *line, int v, int v2, int check2);
int		redir_exp_helper(char **line, int *var, int *var2, int *check);
int		check_spaces(char *expansion);

// expand.c

char	*expand_arg(char *arg);
char	*expand_arg_continue(char *arg, int var, int len, char *temp);
char	*find_final(char *cmd, char *temp);
int		right_len(t_tree *temp);

// expander_check_aux.c

int		in_double_quotes(char *line, int i);
char	*remove_expansion(char *line);
int		arg_len(char *expansion_name);
int		expa_len(char *line);
int		skip_spaces(char *line);

// expander_check.c

int		expand_check(char *line);
char	*expand(char *line, char *key, int start, int end);
char	*expand_caller(char *line);
char	*add_expansion(char *line, char *expansion, int i);
char	*get_expansion(char *line);

// init.c

void	init_shell(char **ev);
void	lvl_upd(int var, char *temp);
void	exp_lvl(int var, int lvl);
t_shell	*shell(void);

// init1,5.c

char	*getpid_self(void);
void	init_env(char **ev);
void	init_exp(char **ev);

// init2.c

char	*find_home(void);
char	*str_redef(char *str, int var, int var2, int except);
char	*copy_no_nl(char *temp);
void	set_alias(int len, int fd);

// init3.c

void	init_alias(void);
void	init_alias2(int fd, char *line, int var, char *home);
void	just_do_it(int var, int var2, int len, char *temp);
void	just_do_it_too(int var, int var2, int len, char *temp);

// init_errs.c

void	init_err1(int check);
void	init_err2(char *temp);
void	init_err3(char *temp, char *temp3);
void	set_alias3(char *line, char *temp, int var, int *len);
void	set_alias2(char *line, int *len, int var, char *temp);
char	*find_home_alias(void);

// commands.c

void	echo_cmd(int flag, char *msg);
void	pwd_cmd(void);
void	exp_cmd(int flag, char *msg, int var);
void	unset_cmd(char *msg);
void	env_cmd(t_tree *tree);

// commands2.c
void	singleton_free(int exit);
void	exit_cmd(t_tree *tree, int code);
void	cd_cmd(char *path);
char	*find_path(char *cmd, int var, char *line, char *temp);
void	exit_help(void);

// cmd_utils.c

char	**exp_set(char *msg, char **temp, int var);
char	**env_set(char *msg);
char	**exp_redef(int var2, char *msg, int var);
char	**env_redef(int var2, char *msg, int var);
size_t	exp_len(const char *s);

// cmd_utils2.c

void	switch_str(int var);
char	**re_write_exp(char *msg, int v, int v2);
char	**re_write_env(char *msg, int v, int v2);

// cmd_utils3.c

char	*set_blank(char *msg);
char	**quoting_set(int var);
char	*exp_strdup(const char *s1);
int		error_syntax(char *array);
int		long_check(char *str);

// cmd_utils4.c

void	set_old_path(int var, int var2, int len, char *temp);
void	old_path_exp(int var, int var2, int len, char *temp);
void	set_new_path(int var, char *newpath, char *temp);
void	new_path_exp(int var, char *temp);
void	mv_home(void);

// cmd_utils5.c

void	mv_old(void);
void	mv_abs(char *path);
char	**hist_manage(char *line, int flag);
int		redir_input(t_tree	*redir);

// cmd_utils6.c

int		trunc_help(char *temp, char *value);
void	exp_organize(void);
void	second_organize(int var, int var2);

// get_next_line

char	*get_next_line(int fd);
int		ft_linelen_gnl(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	ft_buffer_clean(char *str);

#endif