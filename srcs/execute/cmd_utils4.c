/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:08:40 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/18 13:55:30 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_old_path(void)
{
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "OLDPWD=", 7))
		{
			while (shell()->env[var2])
			{
				if (!ft_strncmp(shell()->env[var2], "PWD=", 4))
				{
					free(shell()->env[var]);
					shell()->env[var] = ft_calloc(sizeof(char), ft_strlen(shell()->env[var2]) + 5);
					ft_strcpy(shell()->env[var], "OLDPWD=");
					ft_strcpy(shell()->env[var] + 7, shell()->env[var2] + 4);
					break ;
				}
				var2++;
			}
		}
		var++;
	}
	old_path_exp();
}

void	old_path_exp(void)
{
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], "OLDPWD=", 7))
		{
			while (shell()->exp[var2])
			{
				if (!ft_strncmp(shell()->exp[var2], "PWD=", 4))
				{
					free(shell()->exp[var]);
					shell()->exp[var] = ft_calloc(sizeof(char), ft_strlen(shell()->exp[var2]) + 5);
					ft_strcpy(shell()->exp[var], "OLDPWD=");
					ft_strcpy(shell()->exp[var] + 7, shell()->exp[var2] + 4);
					break ;
				}
				var2++;
			}
		}
		var++;
	}
}

void	set_new_path(void)
{
	int		var;
	char	buf[1000];
	char	*newpath;

	var = 0;
	newpath = getcwd(buf, sizeof(buf));
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "PWD=", 4))
		{
			free(shell()->env[var]);
			shell()->env[var] = ft_calloc(sizeof(char), ft_strlen(newpath) + 5);
			ft_strcpy(shell()->env[var], "PWD=");
			ft_strcpy(shell()->env[var] + 4, newpath);
			break ;
		}
		var++;
	}
	new_path_exp();
}

void	new_path_exp(void)
{
	int		var;
	char	buf[1000];
	char	*newpath;

	var = 0;
	newpath = getcwd(buf, sizeof(buf));
	while (shell()->exp[var])
	{
		if (!ft_strncmp(shell()->exp[var], "PWD=", 4))
		{
			free(shell()->exp[var]);
			shell()->exp[var] = ft_calloc(sizeof(char), ft_strlen(newpath) + 7);
			ft_strcpy(shell()->exp[var], "PWD=\"");
			ft_strcpy(shell()->exp[var] + 5, newpath);
			shell()->exp[var][ft_strlen(shell()->exp[var])] = '\"';
			break ;
		}
		var++;
	}
}

void	mv_home(void)
{
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	while (shell()->env[var])
	{
		if (!ft_strncmp(shell()->env[var], "HOME=", 5))
		{
			while (shell()->env[var][var2] != '=')
				var2++;
			chdir(shell()->env[var] + var2 + 1);
			set_old_path();
			set_new_path();
		}
		var++;
	}
}
