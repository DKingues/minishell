/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:01:51 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 18:02:04 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*normie_expander(char *temp, int var, int len, char *arg)
{
	temp = ft_strdup(shell()->exp[var] + len + 1);
	if (!temp)
	{
		free(arg);
		malloc_err(NULL, "malloc");
	}
	temp = ft_strjoin(temp, arg + len + 1);
	if (!temp)
	{
		free(arg);
		malloc_err(NULL, "malloc");
	}
	return (temp);
}
