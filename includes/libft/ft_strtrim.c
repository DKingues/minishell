/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:55:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/31 15:50:49 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	to_trim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (0);
	while (to_trim(set, s1[i]))
		i++;
	while (to_trim(set, s1[j]))
		j--;
	dst = ft_substr(s1, i, (j - i) + 1);
	if (!dst)
		return (NULL);
	return (dst);
}
/*int	main (void)
{
	char s1[] = "1233312355555123";
	char s2[] = "";
	char s3[] = "123123123";
	
	printf("String should be 55555: %s\n", ft_strtrim(s1, "123"));
	printf("String should be empty: %s\n", ft_strtrim(s2, "dasd"));
	printf("String should be 123123123: %s\n", ft_strtrim(s3, ""));
	printf("String should be empty: %s\n", ft_strtrim(s3, "123"));
}*/