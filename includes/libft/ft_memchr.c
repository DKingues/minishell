/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:12:39 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/12 17:37:15 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	size_t			i;
	unsigned char	caster;

	string = (unsigned char *)s;
	i = 0;
	caster = c;
	while (i < n)
	{
		if (string[i] == caster)
			return ((void *)&string[i]);
		i++;
	}
	return (NULL);
}
