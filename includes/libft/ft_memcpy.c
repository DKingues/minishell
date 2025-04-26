/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:24:36 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/13 19:59:01 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	const char		*u;
	size_t			i;

	p = dst;
	u = src;
	i = 0;
	while (i < n && (src || dst))
	{
		p[i] = u[i];
		i++;
	}
	return (dst);
}
