/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:02:50 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/21 17:42:22 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

char	*ft_write_word(const char *str, char c)
{
	size_t	k;
	size_t	x;
	char	*mal;

	k = 0;
	x = 0;
	while (str[x] && str[x] != c)
		x++;
	mal = ft_calloc(sizeof(char), x + 1);
	if (!mal)
		return (NULL);
	while (str[k] && str[k] != c)
	{
		mal[k] = str[k];
		k++;
	}
	return (mal);
}

void	ft_free_split(char **mal)
{
	size_t	i;

	i = 0;
	while (mal[i] != NULL)
	{
		free(mal[i]);
		i++;
	}
	if (mal)
		free(mal);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	char	**mal;

	j = 0;
	i = 0;
	if (!s)
		return (ft_calloc(1, 1));
	mal = ft_calloc(sizeof(char *), ft_count_words(s, c) + 1);
	if (!mal)
		return (NULL);
	while (j < ft_count_words(s, c))
	{
		while (s[i] == c)
			i++;
		mal[j] = ft_write_word(&s[i], c);
		if (!mal[j])
		{
			ft_free_split(mal);
			return (NULL);
		}
		i += ft_strlen(mal[j]);
		j++;
	}
	return (mal);
}
