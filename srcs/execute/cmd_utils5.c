/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:03:49 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/14 16:21:07 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mv_old(void)
{
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	while (shell()->env[var])
		{
			if (!ft_strncmp(shell()->env[var], "OLDPWD=", 7))
			{
				while(shell()->env[var][var2] != '=')
					var2++;
				chdir(shell()->env[var] + var2 + 1);
				set_old_path();
				set_new_path();
				pwd_cmd();
			}
			var++;
		}
}

void	mv_abs(char *path)
{
	char	*abs_path;
	int		var;

	var = 0;
	while(ft_strncmp(shell()->env[var], "HOME=", 5))
		var++;
	if(!shell()->env[var])
		return ;
	abs_path = ft_strdup(shell()->env[var] + 5);
	abs_path = ft_strjoin(abs_path, path + 1);
	if(!access(abs_path, 0))
	{
		chdir(abs_path);
		set_old_path();
		set_new_path();
	}
}

char **hist_manage(char *line, int flag)
{
	char **temp;
	int	var;
	
	var = 0;
	if (!line[0] || line[0] == '\n')
		return (shell()->hist);
	if (flag)
		return(ft_free_split(shell()->hist), rl_clear_history(), ft_calloc(sizeof(char *), 1));
	add_history(line);
	while(shell()->hist[var])
		var++;
	temp = ft_calloc(sizeof(char *), var + 2);
	var = 0;
	while(shell()->hist[var])
	{
		temp[var] = ft_strdup(shell()->hist[var]);
		if(!ft_strncmp(line, "history", 7))
			ft_printf(1, "    %d  %s\n", var + 1, temp[var]);
		var++;
	}
	temp[var] = ft_strdup(line);
	if(!ft_strncmp(line, "history", 7))
		ft_printf(1, "    %d  %s\n", var + 1, temp[var]);
	return(ft_free_split(shell()->hist), temp);
}

/* void	redir_input(char *info, char *path)
{
	int	fd;
	
	if(info[0] == '<')
	{
		if(info[1] == '<')
			here_doc();
		else
		{
			fd = open(path, O_RDONLY);
			dup2(fd, 0);
		}
	}
	else
	{
		if (info[1] == '>')
		{
			fd = open(path, O_RDONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, 1);
		}
		else
		{
			fd = open(path, O_RDONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, 1);
		}
	}
} */
