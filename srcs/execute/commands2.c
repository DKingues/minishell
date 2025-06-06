/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:30 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/06/06 15:32:36 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_cmd(char *msg, int mult_args)
{
	int	code;
	
	code = error_syntax(msg);
	if (mult_args)
		return (1);
	if (code == 0 || long_check(msg))
		code = 2;
	else
		code = ft_atoi(msg);
	exit(code);
}

void	cd_cmd(char *path)
{
	
	if (!access(path, 0))
	{
		chdir(path);
		set_old_path();
		set_new_path();
	}
	else if (path[0] == '-')
		mv_old();
	else if (!path[0] || (path[0] == '~' && !path[1]))
		mv_home();
	else if (path[0] == '~' && path[1])
		mv_abs(path);
	else
		printf("Error3");
}

char	*find_path(char *cmd)
{
	char	**path;
	char	*line;
	char	*temp;
	int		var;

	var = 0;
	while (ft_strnstr(shell()->env[var], "PATH", 4) == 0 && shell()->env[var + 1])
		var++;
	if (!shell()->env[var + 1])
		return (cmd);
	path = ft_split(shell()->env[var] + 5, ':');
	var = 0;
	while (path[var] != NULL)
	{
		temp = ft_nfstrjoin(path[var], "/");
		line = ft_strjoin(temp, cmd);
		if (access(line, 0) == 0)
			return (ft_free_split(path), line);
		free(line);
		var++;
	}
	return (ft_free_split(path), cmd);
}
