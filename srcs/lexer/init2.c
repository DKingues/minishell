/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:32:35 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/26 15:04:33 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_home_alias(void)
{
	char *current;
	char path[1000];
	int var = 7;
	int	var2 = 0;
	char *res;
	current = ft_strdup(getcwd(path, sizeof(path)));
	if (!ft_strncmp(current, "/home/", 6))
	{
		while(current[var] && current[var] != '/')
			var++;
		res = ft_calloc(sizeof(char), var + 1);
		if (!res)
			return (NULL);
		while(current[var2] && var2 < var)
		{
			res[var2] = current[var2];
			var2++;
		}
		return (free(current), res);
	}
	else
		return (free(current), NULL);
}

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

char	*str_redef(char *str, int var, int var2, int except)
{
	char	*res;

	except = 2;
	if ((str[0] == '\'' && str[ft_strlen(str) - 2] != '\'')
		|| (str[0] != '\'' && str[ft_strlen(str) - 2] == '\''))
		return (NULL);
	if ((str[0] == '\"' && str[ft_strlen(str) - 2] != '\"')
		|| (str[0] != '\"' && str[ft_strlen(str) - 2] == '\"'))
		return (NULL);
	if (str[0] != '\'' && str[0] != '\"')
		except = 0;
	while (str[var] && str[var] != '\n')
		var++;
	if (except == 0)
		var2 = 0;
	res = ft_calloc(sizeof(char), var - except + 1);
	if (!res)
		return (NULL);
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
	if (!res)
		return (free(temp), NULL);
	while (temp[var] != '\n')
	{
		res[var] = temp[var];
		var++;
	}
	if (temp)
		free(temp);
	return (res);
}

void	set_alias(int len, int fd)
{
	char	*line;
	int		var;

	shell()->alias = ft_calloc(sizeof(char *), len + 1);
	if (!shell()->alias)
	{
		close(fd);
		if (shell()->env)
			ft_free_split(shell()->env);
		if (shell()->exp)
			ft_free_split(shell()->exp);
		exit(1);
	}
	line = get_next_line(fd);
	len = 0;
	while (line)
	{
		var = 6;
		if (!ft_strncmp("alias ", line, 6))
			set_alias2(line, &len, var, NULL);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	set_alias2(char *line, int *len, int var, char *temp)
{
	char	*temp2;
	char	*temp3;

	temp = str_redef(line + exp_len(line) + 1, 0, 1, 0);
	if (!temp)
	{
		if (shell()->alias)
			ft_free_split(shell()->alias);
		if (shell()->env)
			ft_free_split(shell()->env);
		if (shell()->exp)
			ft_free_split(shell()->exp);
		exit(1);
	}
	if (temp[ft_strlen(temp) - 1] == '\n')
	{
		temp = copy_no_nl(temp);
		if (temp)
		{
			if (shell()->alias)
				ft_free_split(shell()->alias);
			if (shell()->env)
				ft_free_split(shell()->env);
			if (shell()->exp)
				ft_free_split(shell()->exp);
			exit(1);
		}
	}
	while (line[var] != '=')
		var++;
	temp2 = ft_calloc(sizeof(char), var + 2);
	if (!temp2)
	{
		if (temp)
			free(temp);
		if (shell()->alias)
			ft_free_split(shell()->alias);
		if (shell()->env)
			ft_free_split(shell()->env);
		if (shell()->exp)
			ft_free_split(shell()->exp);
		exit(1);
	}
	var = 0;
	while (line[var + 6] != '=')
	{
		temp2[var] = line[var + 6];
		var++;
	}
	temp2[var] = '=';
	temp3 = ft_strjoin(temp2, temp);
	if (!temp3)
	{
		if (temp)
			free(temp);
		if (shell()->alias)
			ft_free_split(shell()->alias);
		if (shell()->env)
			ft_free_split(shell()->env);
		if (shell()->exp)
			ft_free_split(shell()->exp);
		exit(1);
	}
	shell()->alias[*len] = ft_strdup(temp3);
	if (!shell()->alias[*len])
	{
		if (temp)
			free(temp);
		if (temp3)
			free(temp3);
		if (shell()->alias)
			ft_free_split(shell()->alias);
		if (shell()->env)
			ft_free_split(shell()->env);
		if (shell()->exp)
			ft_free_split(shell()->exp);
		exit(1);
	}
	free(temp3);
	(*len)++;
	free(temp);
}
