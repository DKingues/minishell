/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:15:50 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/24 16:46:16 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_c_counter(char *str, char c)
{
	size_t counter;

	counter = 0;
	while (*str)
	{
		if (*str == c)
			counter++;
		str++;
	}
	return (counter);
}
char	*ft_delcpy(char *str, char c)
{
	size_t	i;
	size_t	j;
	char 	*new_line;
	
	i = 0;
	j = 0;
	new_line = ft_calloc(sizeof(char), (ft_strlen(str) - ft_c_counter(str, c)) + 1);
	if (!str)
		return (NULL);
	if (!c)
		return (str);
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
			new_line[j++] = str[i++];
	}
	return (new_line);
}
