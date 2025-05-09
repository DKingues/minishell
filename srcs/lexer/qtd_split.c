// #include "minishell.h"
#include <stdio.h>

int	ft_count_words(char *str, char delimiter)
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
		if (str[i] == delimiter || str[i + 1] == '\0')
			counter++;
		i++;
	}
	return (counter);
}

int main ()
{
	printf("String[%s]\tArg Counter: [%d]\n", "Spi \"diogo wow 2x\' asd d", ft_count_words("Spi \"diogo wow 2x\' asd d", ' '));
	printf("String[%s]\tArg Counter: [%d]\n", "Spi     \"diogo     wow 2x\" asd d", ft_count_words("Spi \"diogo     wow 2x\" asd d", ' '));
	printf("String[%s]\tArg Counter: [%d]\n", "Spi \'diogo wow 2x\' asd d", ft_count_words("Spi \'diogo wow 2x\" asd d", ' '));
	printf("String[%s]\tArg Counter: [%d]\n", "Spi \"\" diogo wow 2x\" asd d", ft_count_words("Spi \"\"diogo wow 2x\" asd d", ' '));
	printf("String[%s]\tArg Counter: [%d]\n", "Spi \"diogo wow 2x\" \' asd d", ft_count_words("Spi \"diogo wow 2x\"  \'asd d", ' '));
}

// char **ft_split(char *str, char delimiter)
// {
// 	int	i;

// 	i = 0;
// 	if (count_quotes(str) % 2 != 0);
// 		return(ft_putendl_fd("Error: Unmatched quotes", 2), NULL);
//
// 
// 
// }
