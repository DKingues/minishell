/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:40:29 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/21 14:43:29 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cast;

	cast = c;
	i = ft_strlen(s);
	if (c == '\0')
	{
		return ((char *)&s[i]);
	}
	while (i >= 0)
	{
		if (s[i] == cast)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*int	main(void)
{
	printf("%s\n", strrchr(NULL, 10));
	printf("%s\n", ft_strrchr(NULL, 10));
	return (0);
}*/