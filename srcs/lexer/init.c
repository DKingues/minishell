/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:01 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/15 16:13:57 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_home(void)
{
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "HOME=", 5))
			return(ft_strdup(shell()->env[var] + 5));
		var++;
	}
	return (NULL);
}

char *str_redef(char *str)
{
	int	var;
	char *res;
	int	except;
	int	var2;

	except = 2;
	var = 0;
	var2 = 1;
	if((str[0] == '\'' && str[ft_strlen(str) - 2] != '\'') || (str[0] != '\'' && str[ft_strlen(str) - 2] == '\''))
		return(NULL);
	if((str[0] == '\"' && str[ft_strlen(str) - 2] != '\"') || (str[0] != '\"' && str[ft_strlen(str) - 2] == '\"'))
		return(NULL);
	if(str[0] != '\'' && str[0] != '\"')
		except = 0;
	while(str[var] && str[var]  != '\n')
		var++;
	if(except == 0)
		var2 = 0;
	res = ft_calloc(sizeof(char), var - except + 1);
	var = 0;
	while(str[var + except] != '\0' && str[var + except] != '\n')
	{
		res[var] = str[var + var2];
		var++;
	}
	return(res);
}

char *copy_no_nl(char *temp)
{
	char *res;
	int	var;
	
	var = 0;
	res = ft_calloc(sizeof(char), ft_strlen(temp));
	while(temp[var] != '\n')
	{
		res[var] = temp[var];
		var++;
	}
	if(temp)
		free(temp);
	return(res);
}

void	set_alias(int len)
{
	int	fd;
	char	*line;
	char *temp;
	char *temp2;
	char *home = find_home();
	int	var;
	
	home = ft_strjoin(home, "/.zshrc");
	fd = open(home, O_RDONLY);
	if(fd == -1)
	{
		shell()->alias = ft_calloc(1, sizeof(char *));
		shell()->alias[0] = ft_strdup("");
		return ;
	}
	shell()->alias = ft_calloc(sizeof(char *), len + 1);
	line = get_next_line(fd);
	len = 0;
	while(line)
	{
		var = 6;
		if(!ft_strncmp("alias ", line, 6))
		{
			temp = str_redef(line + exp_len(line) + 1);
			if(!temp)
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			if(temp[ft_strlen(temp) - 1] == '\n')
				temp = copy_no_nl(temp);
			while(line[var] != '=')
				var++;
			temp2 = ft_calloc(sizeof(char), var + 2);
			var = 0;
			while(line[var + 6] != '=')
			{
				temp2[var] = line[var + 6];
				var++;
			}
			temp2[var] = '=';
			shell()->alias[len] = ft_strjoin(temp2, temp);
			len++;
			free(temp);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(home);
	free(line);
	close(fd);
}

void	init_alias(void)
{
	int	fd;
	char *line;
	int	var;
	char *home = find_home();
	var = 0;
	home = ft_strjoin(home, "/.zshrc");
	fd = open(home, O_RDONLY);
	if(fd == -1)
	{
		shell()->alias = ft_calloc(1, sizeof(char *));
		shell()->alias[0] = ft_strdup("");
		return ;
	}
	line = get_next_line(fd);
	while(line)
	{
		if(!ft_strncmp("alias ", line, 6))
			var++;
		free(line);
		line = get_next_line(fd);
	}
	free(home);
	free(line);
	close(fd);
	set_alias(var);
}

void init_shell(char **ev)
{
	init_env(ev);
	init_exp(ev);
	init_alias();
	shell()->count = 0;
	shell()->tree = NULL;
	shell()->hist = ft_calloc(sizeof(char *), 1);
	shell()->exit = 0;
	shell()->pipe_count = 0;
	shell()->in = 0;
	shell()->out = 0;
}

void	init_env(char **ev)
{
	int	var;
	
	var = 0;
	if(ev[0])
	{
		while(ev[var])
			var++;
		shell()->env = ft_calloc(sizeof(char *), var + 1);
		var = 0;
		while (ev[var])
		{
			shell()->env[var] = ft_strdup(ev[var]);
			var++;
		}
		lvl_upd();
	}
	else
	{
		shell()->env = ft_calloc(sizeof(char *), 1);
		shell()->env[0] = ft_calloc(sizeof(char), 1);
	}
}

void	init_exp(char **ev)
{
	int	var;
	
	var = 0;
	if(ev[0])
	{
		while(ev[var])
			var++;
		shell()->exp = ft_calloc(sizeof(char *), var + 1);
		var = 0;
		while (ev[var])
		{
			shell()->exp[var] = ft_strdup(ev[var]);
			var++;
		}
		exp_organize();
		exp_lvl();
		shell()->exp = quoting_set();
	}
	else
	{
		shell()->exp = ft_calloc(sizeof(char *), 1);
		shell()->exp[0] = ft_calloc(sizeof(char), 1);
	}
}

void	lvl_upd(void)
{
	int	var;
	int	lvl;
	char *temp;

	var = 0;
	while(shell()->env[var])
	{
		if(!ft_strncmp(shell()->env[var], "SHLVL=", 6))
		{
			if (shell()->env[var][6] == '-' || ft_atoui(shell()->env[var] + 6) >= INT_MAX)
				lvl = -1;
			else
				lvl = ft_atoi(shell()->env[var] + 6);
			temp = ft_itoa(lvl + 1);
			free(shell()->env[var]);
			shell()->env[var] = ft_strdup("SHLVL=");
			shell()->env[var] = ft_strjoin(shell()->env[var], temp);
			free(temp);
			break ;
		}
		var++;
	}
}

void	exp_lvl(void)
{
	int	var;
	int	lvl;
	char *temp;

	var = 0;
	while(shell()->exp[var])
	{
		if(!ft_strncmp(shell()->exp[var], "SHLVL=", 6))
		{
			if (shell()->exp[var][6] == '-' || ft_atoui(shell()->exp[var] + 6) >= INT_MAX)
				lvl = -1;
			else
				lvl = ft_atoi(shell()->exp[var] + 6);
			temp = ft_itoa(lvl + 1);
			free(shell()->exp[var]);
			shell()->exp[var] = ft_strdup("SHLVL=");
			shell()->exp[var] = ft_strjoin(shell()->exp[var], temp);
			free(temp);
			break ;
		}
		var++;
	}
}

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}
