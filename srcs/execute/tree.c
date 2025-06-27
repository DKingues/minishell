/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:41:40 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/06/27 11:59:47 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_check(char *flags, char *valid)
{
	int	var;
	int	var2;

	var = 1;
	if(!flags[1])
		return (1);
	while(flags[var])
	{
		var2 = 0;
		while(valid[var2])
		{
			if(flags[var] != valid[var2])
				return (1);
			var2++;
		}
		var++;	
	}
	return (0);
}

char    **args_join(t_tree  *cmd)
{
    int var;
    char    **res;
    t_tree  *temp;
    
    var = 0;
    temp = cmd;
    while(temp)
    {
        var++;
        temp = temp->right;
    }
    res = ft_calloc(sizeof(char *), var + 1);
    var = 0;
    while(cmd)
	{
		res[var] = ft_strdup(cmd->value);
		cmd = cmd->right;
		var++;
	}
	return(res);
}

int	is_builtin(char *cmd)
{
	if(!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1)
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
	t_tree	*temp;
	int	flag;
	char *str;
	flag = 0;
	temp = tree;

	if(!ft_strncmp(temp->value, "export", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if(!temp || !temp->value)
			exp_cmd(0, NULL);
		while(temp)
		{
			exp_cmd(1, temp->value);
			temp = temp->right;	
		}
	}
	else if(!ft_strncmp(temp->value, "echo", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if(temp && temp->value)
		{
			while (temp->value[0] == '-')
			{
				flag = !flag_check(temp->value, "n");
				if(!flag)
					break ;
				temp = temp->right;
			}
			if(!temp && flag)
				return;
			str = ft_strdup(temp->value);
			temp = temp->right;
			while(temp)
			{
				str = ft_strjoin(str, " ");
				str = ft_strjoin(str, temp->value);
				temp = temp->right;
			}
			echo_cmd(flag, str);
			if(str)
				free(str);
		}
		else
			ft_printf(1, "\n");
	}
	else if(!ft_strncmp(temp->value, "exit", ft_strlen(temp->value) + 1))
	{
		if(tree->right)
			exit_cmd(tree->right);
		else
			exit_cmd(NULL);
	}
	else if(!ft_strncmp(temp->value, "unset", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		while(temp)
		{
			unset_cmd(temp->value);
			temp = temp->right;
		}
	}
	else if(!ft_strncmp(temp->value, "pwd", ft_strlen(temp->value) + 1))
		pwd_cmd();
	else if(!ft_strncmp(temp->value, "env", ft_strlen(temp->value) + 1))
		env_cmd(temp);
	else if(!ft_strncmp(temp->value, "cd", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if(temp && temp->value)
		{
			if(temp->right && temp->right->value)
				ft_printf(2, "cd: too many arguments");
			else
				cd_cmd(temp->value);
			return ;
		}
		else
			cd_cmd(NULL);
	}
	else if(!ft_strncmp(temp->value, "history", ft_strlen(temp->value) + 1))
	{
		temp = temp->right;
		if(!temp || !temp->value)
		{
			while(shell()->hist[flag])
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
			while(temp->value[flag])
			{
				if(!ft_isdigit(temp->value[flag]))
				{
					ft_printf(2, "bash: history: %s: numeric argument required\n", temp->value);
					return ;
				}
				flag++;
			}
			flag = ft_atoi(temp->value);
			int	var = 0;
			while(shell()->hist[var])
				var++;
			while(flag > 0)
			{
				var--;
				flag--;
			}
			if(var < 0)
				var = 0;
			while(shell()->hist[var])
			{
				ft_printf(1, "    %d  %s\n", var + 1, shell()->hist[var]);
				var++;
			}
		}
	}
	close_fds();
}

void    execute(t_tree  *cmd)
{
	int	var = 0;
	char    *path;
	char **args;

	if (is_builtin(cmd->value))
	{
		builtin_exec(cmd);
		return ;
	}
	path = find_path(cmd->value);
	args = args_join(cmd);
	singleton_free(0);
	close_fds();
	if(execve(path, args, shell()->env) == -1)
	{
		if(var != -2)
			perror("EXEC2: ");
		else
		{
			while(shell()->env)
			{
				if(ft_strnstr(shell()->env[var], "PATH", 4))
				{
					ft_printf(2, "%s: command not found\n", path);
				}
			}
		}
	}
	ft_free_split(args);
	free(path);
}

int redir_input(t_tree  *redir)
{
	int fd;

	if(redir->type == READ)
	{
		fd = open(redir->value, O_RDONLY);
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
		dup2(fd, 1);
		return (0);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, 1);
		return (0);
	}
	return(1);
}

int waitpids(int *pids, int var)
{
	int code;
	int	i;

	i = 0;
	code = 0;
	while(i < var)
	{
		waitpid(pids[i], &code, 0);
		i++;
	}
	free(pids);
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
		if (!ft_strncmp(eof, line, len + 1))
		{
			free(line);
			shell()->exit = 0;
			close_fds();
			return ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	manage_here_doc(void)
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
		return ;
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
				here_doc(temp->value, fd[1]);
				close(fd[1]);
				shell()->docs[count] = fd[0];
				count++;
			}
			temp = temp->left;
		}
		tree = tree->right;
	}
}

void    tree_executer(void)
{
	int fd[2];
	int var = 0;
	int *pids;
	int check = 0;
	t_tree *temp;

	pids = ft_calloc(shell()->pipe_count + 2, sizeof(int));
	shell()->count = 0;
	while(shell()->tree)
	{
		if(shell()->tree->type == PIPE)
		{   
			if (pipe(fd) == -1)
				return ;	
			check = 1;
		}
		temp = shell()->tree->left;
		pids[var] = fork();
		if(!pids[var])
		{
			if(check == 1)
				dup2(fd[1], 1); //printf("DUPING FD[1]\n");
			if(shell()->tree->type == READ || shell()->tree->type == HERE_DOC || shell()->tree->type == TRUNCATE || shell()->tree->type == APPEND)
				redir_input(shell()->tree); //printf("BF REDIRECTING\n");
			while(temp)
			{
				if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
					redir_input(temp); //printf("LOOP REDIRECTING\n");
				temp = temp->left;
			}
			if(shell()->tree->type == COMMAND && shell()->tree->value)
				execute(shell()->tree); //printf("SELF EXECUTING\n");
			if(shell()->tree->left->type == COMMAND && shell()->tree->left->value)
				execute(shell()->tree->left); //printf("LEFT EXECUTING\n");
			if(shell()->env)
				ft_free_split(shell()->env);
			close_fds();
			exit(0);
		}
		else
		{
			temp = shell()->tree;
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
		var++;
		shell()->tree = shell()->tree->right;
	}
	singleton_free(1);
	close_fds();
	exit(waitpids(pids, var));
}

void    nptree_executer(void)
{
	int var = 0;
	t_tree *temp;

	shell()->count = 0;
	temp = shell()->tree->left;
	if(shell()->tree && shell()->tree->value && shell()->tree->type == COMMAND && is_builtin(shell()->tree->value))
	{
		while(temp)
		{
			if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
				redir_input(temp);
			temp = temp->left;
		}
		if(temp && temp->value &&!ft_strncmp(temp->value, "exit", ft_strlen(temp->value) + 1))
			ft_printf(1, "exit\n");
		execute(shell()->tree);
	}
	else
	{	
		shell()->pid = fork();
		if(!shell()->pid)
		{
			if(shell()->tree->type == READ || shell()->tree->type == HERE_DOC || shell()->tree->type == TRUNCATE || shell()->tree->type == APPEND)
				redir_input(shell()->tree); //printf("BF REDIRECTING\n");
			while(temp)
			{
				if(temp->type == READ || temp->type == HERE_DOC || temp->type == TRUNCATE || temp->type == APPEND)
					redir_input(temp); //printf("LOOP REDIRECTING\n");
				temp = temp->left;
			}
			if(shell()->tree->type == COMMAND && shell()->tree->value)
				execute(shell()->tree); //printf("SELF EXECUTING\n");
			if(shell()->env)
				ft_free_split(shell()->env);
			close_fds();
			exit(0);
		}
		else
			waitpid(shell()->pid, &var, 0);
		shell()->exit = var / 256;
	}
}
