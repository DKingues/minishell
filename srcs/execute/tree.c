/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:41:40 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/17 18:22:21 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_check(char *flags, char *valid)
{
	int	var;
	int	var2;

	var = 1;
	if (!flags[1])
		return (1);
	while (flags[var])
	{
		var2 = 0;
		while (valid[var2])
		{
			if (flags[var] != valid[var2])
				return (1);
			var2++;
		}
		var++;
	}
	return (0);
}

char	**args_join(t_tree	*cmd)
{
	int		var;
	char	*home;
	char	**res;
	t_tree	*temp;

	var = 0;
	temp = cmd;
	home = find_home();
	while (temp)
	{
		var++;
		temp = temp->right;
	}
	res = ft_calloc(sizeof(char *), var + 1);
	var = 0;
	while (cmd)
	{
		if (cmd->value[0] == '~' && cmd->value[1] == '/')
			res[var] = ft_nfstrjoin(home, cmd->value + 1);
		else
			res[var] = ft_strdup(cmd->value);
		cmd = cmd->right;
		var++;
	}
	return (free(home), res);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "env", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1)
		|| !ft_strncmp(cmd, "history", ft_strlen(cmd) + 1))
		return (1);
	return (0);
}

void	builtin_exec(t_tree *tree)
{
	int		flag;
	t_tree	*temp;
	char	*str;

	flag = 0;
	temp = tree;
	if (!ft_strncmp(temp->value, "export", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if (!temp || !temp->value)
			exp_cmd(0, NULL, 0);
		while (temp)
		{
			exp_cmd(1, temp->value, 0);
			temp = temp->right;
		}
	}
	else if (!ft_strncmp(temp->value, "echo", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if (temp && temp->value)
		{
			while (temp && temp->value[0] == '-')
			{
				flag = !flag_check(temp->value, "n");
				if (!flag)
					break ;
				temp = temp->right;
			}
			if (!temp && flag)
				return ;
			str = ft_strdup(temp->value);
			temp = temp->right;
			while (temp)
			{
				str = ft_strjoin(str, " ");
				str = ft_strjoin(str, temp->value);
				temp = temp->right;
			}
			echo_cmd(flag, str);
			if (str)
				free(str);
		}
		else
			ft_printf(1, "\n");
	}
	else if (!ft_strncmp(temp->value, "exit", ft_strlen(temp->value) + 1))
	{
		if (tree->right)
			exit_cmd(tree->right, 0);
		else
			exit_cmd(NULL, 0);
	}
	else if (!ft_strncmp(temp->value, "unset", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		while (temp)
		{
			unset_cmd(temp->value);
			temp = temp->right;
		}
	}
	else if (!ft_strncmp(temp->value, "pwd", ft_strlen(temp->value) + 1))
		pwd_cmd();
	else if (!ft_strncmp(temp->value, "env", ft_strlen(temp->value) + 1))
		env_cmd(temp);
	else if (!ft_strncmp(temp->value, "cd", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if (temp && temp->value)
		{
			if (temp->right && temp->right->value)
			{
				ft_printf(2, "minishell: cd: too many arguments\n");
				shell()->exit = 1;
			}
			else
				cd_cmd(temp->value);
			return ;
		}
		else
			cd_cmd(NULL);
	}
	else if (!ft_strncmp(temp->value, "history", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if (!temp || !temp->value)
		{
			while (shell()->hist[flag])
			{
				ft_printf(1, "    %d  %s\n", flag + 1, shell()->hist[flag]);
				flag++;
			}
			return ;
		}
		else if (temp->value[0] == '-')
			shell()->hist = hist_manage("", !flag_check(temp->value, "c"));
		else
		{
			while (temp->value[flag])
			{
				if (!ft_isdigit(temp->value[flag]))
				{
					ft_printf(2, "bash: history: %s: numeric argument \
						required\n", temp->value);
					return ;
				}
				flag++;
			}
			flag = ft_atoi(temp->value);
			int	var = 0;
			while (shell()->hist[var])
				var++;
			while (flag > 0)
			{
				var--;
				flag--;
			}
			if (var < 0)
				var = 0;
			while (shell()->hist[var])
			{
				ft_printf(1, "    %d  %s\n", var + 1, shell()->hist[var]);
				var++;
			}
		}
	}
	dup2(shell()->in, 0);
	dup2(shell()->out, 1);
	close_fds();
}

char *search_alias(char *path)
{
	int	var;

	var = 0;
	while(shell()->alias[var])
	{
		if(!ft_strncmp(path, shell()->alias[var], exp_len(shell()->alias[var])))
		{
			free(path);
			path = ft_strdup(shell()->alias[var] + exp_len(shell()->alias[var]) + 1);
			return (path);
		}
		var++;
	}
	return (path);
}

char **split_redef(char **args, t_tree *cmd)
{
	int	var;
	t_tree *temp2;
	char **temp;

	var = 0;
	temp2 = cmd->right;
	while(args[var])
		var++;
	while(temp2)
	{
		temp2 = temp2->right;
		var++;
	}
	temp = ft_calloc(sizeof(char *), var + 1);
	var = 0;
	while(args[var])
	{
		temp[var] = ft_strdup(args[var]);
		var++;
	}
	temp2 = cmd->right;
	while(temp2)
	{
		temp[var] = ft_strdup(temp2->value);
		var++;
		temp2 = temp2->right;
	}
	ft_free_split(args);
	return(temp);
}

void    execute(t_tree  *cmd)
{
	int	var = 0;
	char    *path;
	char **args;
	char *temp;
	int	check = 0;
	
	if (is_builtin(cmd->value))
	{
		builtin_exec(cmd);
		return ;
	}
	if(cmd->value[0] == '~' && cmd->value[1] == '/')
	{
		temp = ft_strjoin(find_home(), cmd->value + 1);
		path = find_path(temp);
		free(temp);
	}
	else
		path = find_path(cmd->value);
	if(access(path, F_OK) && access(path, X_OK))
	{
		temp = ft_strdup(path);
		path = search_alias(path);
		if(!ft_strncmp(temp, path, ft_strlen(path)))
		{
			args = args_join(cmd);
			free(temp);
		}
		else
		{
			args = ft_split(path, ' ');
			args = split_redef(args, cmd);
			free(temp);
			free(path);
			path = find_path(args[0]);
		}
	}
	else
		args = args_join(cmd);
	var = 0;
	while(path[var])
	{
		if(path[var] == '/')
			check = 1;
		var++;
	}
	singleton_free(0);
	close_fds();
	if(execve(path, args, shell()->env) == -1)
	{
		if(!check)
		{
			ft_printf(2, "minishell: %s: command not found\n", path);
			shell()->exit = 127;
		}
		else
		{
			if(!access(path, F_OK))
			{
				if(opendir(path))
					ft_printf(2, "minishell: %s: Is a directory\n", path);
				else
				{
					if(access(path, X_OK))
						temp = ft_nfstrjoin("minishell: ", path);
					else
						temp = ft_nfstrjoin("minishell: ", path);
					perror(temp);
					free(temp);
				}
				shell()->exit = 126;
			}
			else
			{
				temp = ft_nfstrjoin("minishell: ", path);
				perror(temp);
				free(temp);
				shell()->exit = 127;
			}
		}
	}
	ft_free_split(args);
	free(path);
}

int redir_input(t_tree  *redir)
{
	int fd;
	char *temp;
	if(redir->type == READ)
	{
		fd = open(redir->value, O_RDONLY);
		if(fd == -1)
		{
			temp = ft_nfstrjoin("minishell: ", redir->value);
			perror(temp);
			free(temp);
			singleton_free(1);
			exit(1);
		}
		dup2(fd, 0);
		return (0);
	}
	else if(redir->type == HERE_DOC)
	{
		dup2(shell()->docs[shell()->count], 0);
		shell()->count++;
		return (0);
	}
	else if (redir->type == TRUNCATE)
	{
		fd = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if(fd == -1)
		{
			temp = ft_nfstrjoin("minishell: ", redir->value);
			perror(temp);
			free(temp);
			singleton_free(1);
			exit(1);
		}
		dup2(fd, 1);
		return (0);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if(fd == -1)
		{
			temp = ft_nfstrjoin("minishell: ", redir->value);
			perror(temp);
			free(temp);
			singleton_free(1);
			exit(1);
		}
		dup2(fd, 1);
		return (0);
	}
	return(1);
}

int waitpids(int var)
{
	int code;
	int	i;

	i = 0;
	code = 0;
	close(0);
	while(i < var)
	{
		waitpid(shell()->pids[i], &code, 0);
		i++;
	}
	free(shell()->pids);
	return (code / 256);
}

void    close_fds(void)
{
	int var;

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

	while(1)
	{
		line = readline(">");
		if (!line || !ft_strncmp(eof, line, len + 1))
		{
			if(line)
				free(line);
			else
				ft_printf(2, "minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", eof);
			singleton_free(1);
			close_fds();
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	manage_here_doc(void)
{
	t_tree	*tree;
	t_tree	*temp;
	int	count;
	int fd[2];

	count = 0;
	tree = shell()->tree;
	while(tree)
	{
		temp = tree;
		while(temp)
		{
			if(temp->type == HERE_DOC)
				count++;
			temp = temp->left;
		}
		tree = tree->right;
	}
	if(!count)
		return (0) ;
	shell()->docs = ft_calloc(count + 1, sizeof(int));
	count = 0;
	tree = shell()->tree;
	while(tree)
	{
		temp = tree;
		while(temp)
		{
			if(temp->type == HERE_DOC)
			{
				if(pipe(fd) == -1)
					exit(0);
				shell()->pid = fork();
				if(!shell()->pid)
				{
					choose_signal(HDOC);
					close(fd[0]);
					here_doc(temp->value, fd[1]);
				}
				else
				{
					choose_signal(IGNORE);
					close(fd[1]);
					waitpid(shell()->pid, &shell()->exit, 0);
					choose_signal(ROOT);
				}
				shell()->exit = shell()->exit / 256;
				if(shell()->exit == 130)
					return (1);
				shell()->docs[count] = fd[0];
				count++;
			}
			temp = temp->left;
		}
		tree = tree->right;
	}
	return(0);
}

void    tree_executer(void)
{
	int fd[2];
	int var = 0;
	int check = 0;
	t_tree *temp;
	t_tree *temp2;

	shell()->pids = ft_calloc(shell()->pipe_count + 2, sizeof(int));
	shell()->count = 0;
	choose_signal(CHLD);
	temp2 = shell()->tree;
	while(temp2)
	{
		if(temp2->type == PIPE)
		{   
			if (pipe(fd) == -1)
				return ;	
			check = 1;
		}
		temp = temp2->left;
		shell()->pids[var] = fork();
		if(!shell()->pids[var])
		{
			free(shell()->pids);
			if(check == 1)
				dup2(fd[1], 1); //printf("DUPING FD[1]\n");
			if(temp2->type == READ || temp2->type == HERE_DOC || temp2->type == TRUNCATE || temp2->type == APPEND)
				redir_input(temp2); //printf("BF REDIRECTING\n");
			while(temp)
			{
				if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
					redir_input(temp); //printf("LOOP REDIRECTING\n");
				temp = temp->left;
			}
			if(temp2 && temp2->value && temp2->type == COMMAND)
				execute(temp2); //printf("SELF EXECUTING\n");
			else if(temp2->left && temp2->left->value && temp2->left->type == COMMAND)
				execute(temp2->left); //printf("LEFT EXECUTING\n");
			singleton_free(1);
			exit(shell()->exit);
		}
		else
		{
			temp = temp2;
			while(temp)
			{
				if(temp->type == HERE_DOC)
					shell()->count++;
				temp = temp->left;
			}
			if(check == 1)
				dup2(fd[0], 0); //printf("DUPING FD[0]\n");
		}
		check = 0;
		if((temp2 && temp2->value && temp2->type == COMMAND) || (temp2->left && temp2->left->value && temp2->left->type == COMMAND))
			var++;
		temp2 = temp2->right;
	}
	singleton_free(1);
	int code = waitpids(var);
	exit(code);
}

void    nptree_executer(void)
{
	t_tree *temp;
	t_tree *temp2;

	shell()->count = 0;
	temp = shell()->tree->left;
	temp2 = shell()->tree;
	if(temp2 && temp2->value && temp2->type == COMMAND && is_builtin(temp2->value))
	{
		while(temp)
		{
			if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
				redir_input(temp);
			temp = temp->left;
		}
		if(temp2 && temp2->value && !ft_strncmp(temp2->value, "exit", ft_strlen(temp2->value) + 1))
		{	
			dup2(shell()->in, 0);
			dup2(shell()->out, 1);
			ft_printf(1, "exit\n");
		}
		else
			shell()->exit = 0;
		execute(temp2);
		dup2(shell()->in, 0);
		dup2(shell()->out, 1);
		close_fds();
	}
	else
	{
		int	pid = 0;
		shell()->pid = fork();
		if(!shell()->pid)
		{
			choose_signal(HDOC);
			shell()->exit = 0;
			pid = fork();
			if(!pid)
			{
				if(temp2->type == READ || temp2->type == HERE_DOC || temp2->type == TRUNCATE || temp2->type == APPEND)
					redir_input(temp2); //printf("BF REDIRECTING\n");
				while(temp)
				{
					if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
						redir_input(temp); //printf("LOOP REDIRECTING\n");
					temp = temp->left;
				}
				if(temp2->type == COMMAND && temp2->value)
					execute(temp2); //printf("SELF EXECUTING\n");
				if(shell()->env)
					ft_free_split(shell()->env);
				close_fds();
				exit(shell()->exit);
			}
			else
			{
				waitpid(shell()->pid, &shell()->exit, 0);
			}
			singleton_free(1);
			exit(shell()->exit / 256);
		}
		else
		{
			choose_signal(IGNORE);
			waitpid(shell()->pid, &shell()->exit, 0);
			choose_signal(ROOT);
			shell()->exit = shell()->exit / 256; 
		}
	}
}
