/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:26:28 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/11 15:21:49 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_linelen_gnl(char *str)
{
	int	var;

	var = 0;
	while (str && str[var] && str[var] != '\n')
		var++;
	if (str && str[var] == '\n')
		var++;
	return (var);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*mal;
	int		var;
	int		var2;

	var = 0;
	var2 = 0;
	mal = (char *)ft_calloc((ft_linelen_gnl(s1) + ft_linelen_gnl(s2) + 1), 1);
	if (!mal)
		return (free(s1), NULL);
	while (s1 && s1[var])
	{
		mal[var] = s1[var];
		var++;
	}
	while (s2[var2] != '\n' && s2[var2])
	{
		mal[var + var2] = s2[var2];
		var2++;
	}
	if (s2[var2] == '\n')
		mal[var + var2] = '\n';
	if (s1)
		free(s1);
	return (mal);
}

void	ft_buffer_clean(char *str)
{
	int	var;
	int	var2;

	var = 0;
	var2 = 0;
	while (str[var] != '\n' && var < BUFFER_SIZE)
	{
		str[var] = '\0';
		var++;
	}
	if (str[var] == '\n')
	{
		str[var] = '\0';
		var++;
		while (var < BUFFER_SIZE)
		{
			str[var2] = str[var];
			str[var] = '\0';
			var++;
			var2++;
		}
	}
}
