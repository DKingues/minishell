/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:23:29 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/20 19:32:20 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*d;
	unsigned const char		*s;

	i = 0;
	d = dest;
	s = src;
	if (!d && !s)
		return (NULL);
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (d);
}

/*int main() {
   // char str[50] = "Hello, World!";
    
    //printf("Before ft_memmove: '%s'\n", str);
    
    // Use ft_memmove to move part of the string within the same array
	char string[] = "olaola";
	char string2[] = "fds";
	ft_memmove(string + 3, string2, 3);
	 printf("%s\n",string);
    return 0;
}*/