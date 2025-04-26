/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:17:23 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/21 15:09:53 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	caster;

	caster = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == caster)
			return ((char *)&s[i]);
		i++;
	}
	if (caster == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
