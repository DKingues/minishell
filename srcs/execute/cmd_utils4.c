/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:08:40 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/08/04 19:20:07 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_old_path(int var, int var2, int len, char *temp)
{
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "OLDPWD=", 7))
		{
			while (shell()->env[var2])
			{
				if (!ft_strncmp(shell()->env[var2], "PWD=", 4))
				{
					just_do_it(var, var2, len, temp);
					break ;
				}
				var2++;
			}
		}
		var++;
	}
	old_path_exp(0, 0, 0, NULL);
}

void	old_path_exp(int var, int var2, int len, char *temp)
{
	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], "OLDPWD=", 7))
		{
			while (shell()->exp[var2])
			{
				if (!ft_strncmp(shell()->exp[var2], "PWD=", 4))
				{
					just_do_it_too(var, var2, len, temp);
					break ;
				}
				var2++;
			}
		}
		var++;
	}
}

void	set_new_path(int var, char *newpath, char *temp)
{
	char	buf[1000];

	var = 0;
	newpath = getcwd(buf, sizeof(buf));
	if (!newpath)
		return ;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "PWD=", 4))
		{
			free(shell()->env[var]);
			temp = ft_calloc(sizeof(char), ft_strlen(newpath) + 5);
			if (!temp)
				malloc_err(NULL, "malloc");
			ft_strcpy(temp, "PWD=");
			ft_strcpy(temp + 4, newpath);
			shell()->env[var] = ft_strdup(temp);
			free(temp);
			if (!shell()->env[var])
				malloc_err(NULL, "malloc");
			break ;
		}
		var++;
	}
	new_path_exp(0, NULL);
}

void	new_path_exp(int var, char *temp)
{
	char	buf[1000];
	char	*newpath;

	newpath = getcwd(buf, sizeof(buf));
	if (!newpath)
		return ;
	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], "PWD=", 4))
		{
			free(shell()->exp[var]);
			temp = ft_calloc(sizeof(char), ft_strlen(newpath) + 7);
			if (!temp)
				malloc_err(NULL, "malloc");
			ft_strcpy(temp, "PWD=\"");
			ft_strcpy(temp + 5, newpath);
			temp[ft_strlen(temp)] = '\"';
			shell()->exp[var] = ft_strdup(temp);
			free(temp);
			if (!shell()->exp[var])
				malloc_err(NULL, "malloc");
			break ;
		}
		var++;
	}
}

void	mv_home(void)
{
	char	*home;

	home = find_home();
	if (!home)
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		return ;
	}
	chdir(home);
	set_old_path(0, 0, 0, NULL);
	set_new_path(0, NULL, NULL);
	free(home);
}
