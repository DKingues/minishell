/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:24:30 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/05 21:37:51 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*voidptr;
	size_t			i;

	i = 0;
	voidptr = s;
	while (i < n)
	{
		voidptr[i] = 0;
		i++;
	}
}
