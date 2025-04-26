/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:16:30 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/21 14:41:38 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*voidptr;
	size_t			i;

	i = 0;
	voidptr = b;
	while (i < len)
	{
		voidptr[i] = (unsigned char) c;
		i++;
	}
	return (b);
}

//int main() {
//    char str[50] = "Hello, World!";
//    printf("Before memset: '%s'\n", str); 
//    // Use memset to set the first 5 bytes to 'A'
//    memset(NULL, 'A', 5);
//    printf("After memset: '%s'\n", str); // Should print "AAAAA, World!"
//    return 0;
//}
