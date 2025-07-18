/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:48:05 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/18 13:46:36 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*mal;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	mal = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (mal == NULL)
		return (NULL);
	while (i != ft_strlen(s1))
	{
		mal[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		mal[i] = s2[j];
		j++;
		i++;
	}
	free((char *)s1);
	return (mal);
}

char	*ft_nfstrjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*mal;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	mal = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (mal == NULL)
		return (NULL);
	while (i != ft_strlen(s1))
	{
		mal[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		mal[i] = s2[j];
		j++;
		i++;
	}
	return (mal);
}
