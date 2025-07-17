/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:32:35 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/16 18:44:02 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_home(void)
{
	int	var;

	var = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "HOME=", 5))
			return (ft_strdup(shell()->env[var] + 5));
		var++;
	}
	return (NULL);
}

char	*str_redef(char *str)
{
	int		var;
	char	*res;
	int		except;
	int		var2;

	except = 2;
	var = 0;
	var2 = 1;
	if ((str[0] == '\'' && str[ft_strlen(str) - 2] != '\'') || (str[0] != '\'' && str[ft_strlen(str) - 2] == '\''))
		return (NULL);
	if ((str[0] == '\"' && str[ft_strlen(str) - 2] != '\"') || (str[0] != '\"' && str[ft_strlen(str) - 2] == '\"'))
		return (NULL);
	if (str[0] != '\'' && str[0] != '\"')
		except = 0;
	while (str[var] && str[var] != '\n')
		var++;
	if (except == 0)
		var2 = 0;
	res = ft_calloc(sizeof(char), var - except + 1);
	var = 0;
	while (str[var + except] != '\0' && str[var + except] != '\n')
	{
		res[var] = str[var + var2];
		var++;
	}
	return (res);
}

char	*copy_no_nl(char *temp)
{
	char	*res;
	int		var;

	var = 0;
	res = ft_calloc(sizeof(char), ft_strlen(temp));
	while (temp[var] != '\n')
	{
		res[var] = temp[var];
		var++;
	}
	if (temp)
		free(temp);
	return (res);
}

void	set_alias(int len)
{
	int		fd;
	char	*line;
	char	*temp;
	char	*temp2;
	char	*home ;
	int		var;

	home = find_home();
	home = ft_strjoin(home, "/.zshrc");
	fd = open(home, O_RDONLY);
	if (fd == -1)
	{
		shell()->alias = ft_calloc(1, sizeof(char *));
		shell()->alias[0] = ft_strdup("");
		return ;
	}
	shell()->alias = ft_calloc(sizeof(char *), len + 1);
	line = get_next_line(fd);
	len = 0;
	while (line)
	{
		var = 6;
		if (!ft_strncmp("alias ", line, 6))
		{
			temp = str_redef(line + exp_len(line) + 1);
			if (!temp)
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			if (temp[ft_strlen(temp) - 1] == '\n')
				temp = copy_no_nl(temp);
			while (line[var] != '=')
				var++;
			temp2 = ft_calloc(sizeof(char), var + 2);
			var = 0;
			while (line[var + 6] != '=')
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
	int		fd;
	char	*line;
	int		var;
	char	*home;

	var = 0;
	home = find_home();
	home = ft_strjoin(home, "/.zshrc");
	fd = open(home, O_RDONLY);
	if (fd == -1)
	{
		shell()->alias = ft_calloc(1, sizeof(char *));
		shell()->alias[0] = ft_strdup("");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp("alias ", line, 6))
			var++;
		free(line);
		line = get_next_line(fd);
	}
	free(home);
	free(line);
	close(fd);
	set_alias(var);
}
