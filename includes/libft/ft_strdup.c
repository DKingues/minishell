/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:36:31 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/21 15:16:08 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	i;

	tmp = ft_calloc(sizeof(char), ft_strlen(s1) + 1);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < sizeof(char) * (ft_strlen(s1) + 1))
	{
		tmp[i] = s1[i];
		i++;
	}
	return (tmp);
}
