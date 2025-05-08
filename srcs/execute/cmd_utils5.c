/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:03:49 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/05/08 18:26:21 by rmota-ma         ###   ########.fr       */
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
	printf("%s\n", abs_path);
	if(!access(abs_path, 0))
	{
		chdir(abs_path);
		set_old_path();
		set_new_path();
	}
}