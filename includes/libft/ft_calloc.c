/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:37:39 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/21 15:24:57 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;
	size_t			check;

	i = 0;
	check = count * size;
	if (count && (check / count) != size)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	if (count == 0 || size == 0)
		return (tmp);
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}
