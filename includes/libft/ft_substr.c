/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:14:34 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/02 15:36:48 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../srcs/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*mal;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	mal = ft_calloc(sizeof(char), (len + 1));
	if (!mal)
		return (NULL);
	while (i < len)
	{
		mal[i] = s[start + i];
		i++;
	}
	return (mal);
}

char	*proc_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;

	temp = ft_substr(s, start, len);
	if (!temp)
		exit_cmd(NULL, 0);
	return (temp);
}
