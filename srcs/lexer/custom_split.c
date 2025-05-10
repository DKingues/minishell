/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:51:07 by dicosta-          #+#    #+#             */
/*   Updated: 2025/05/10 19:12:57 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_words(char *str)
{
	int i;
	int counter;
	char temp;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			temp = str[i];
			i++;
			while (str[i] && str[i] != temp)
				i++;
			if (str[i] == temp)
				i++;
		}
		if (ft_isspace(str[i]) || str[i + 1] == '\0')
			counter++;
		i++;
	}
	return (counter);
}
char **aloc_parts(char *str)
{
    char **parts;
    parts = ft_calloc(sizeof(char*), ft_count_words(str));
    if (!parts)
        return(free(parts), NULL);
}
int ft_buffed_split(char *str)
{
	int parts;

	if (quote_counter(str) % 2 != 0)
		return(ft_putendl_fd("Error: Unmatched quotes", 2), 0);
    aloc_parts(str);
	ft_printf("STRING: %s\nQUOTES: [%d]\n WORDS: [%d]", str, quote_counter(str), parts);
	return(1);
}