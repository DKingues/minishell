/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:32:35 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/02 16:23:35 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_home_alias(void)
{
	char	*current;
	char	*res;
	char	path[1000];
	int		var;
	int		var2;

	var = 7;
	var2 = 0;
	current = ft_strdup(getcwd(path, sizeof(path)));
	if (!ft_strncmp(current, "/home/", 6))
	{
		while (current[var] && current[var] != '/')
			var++;
		res = ft_calloc(sizeof(char), var + 1);
		if (!res)
			return (NULL);
		while (current[var2] && var2 < var)
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
