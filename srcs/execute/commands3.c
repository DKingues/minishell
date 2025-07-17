/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:05:22 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/17 18:11:18 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_cmd(t_tree *tree)
{
	int	var;

	var = 0;
	if (tree->right && tree->right->value && tree->right->type == ARG)
		ft_printf(2, "env: \'%s\': No such file or directory",
			tree->right->value);
	while (shell()->env[var])
	{
		if (shell()->env[var][0])
			ft_printf(1, "%s\n", shell()->env[var]);
		var++;
	}
}
