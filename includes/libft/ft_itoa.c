/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:18:32 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/20 19:29:27 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_intlen(long nbr)
{
	int	numbers;

	numbers = 0;
	if (nbr < 0)
	{
		numbers++;
		nbr *= -1;
	}
	if (nbr == 0)
	{
		numbers++;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		numbers++;
	}
	return (numbers);
}

char	*ft_itoa(int n)
{
	size_t		i;
	long int	nbrctr;
	long int	nbr;
	char		*str;

	nbrctr = ft_intlen(n);
	i = nbrctr - 1;
	nbr = n;
	str = ft_calloc(sizeof(char), (nbrctr + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		str[0] = '-';
	}
	if (nbr == 0)
		str[i] = '0';
	while (nbr != 0)
	{
		str[i] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		i--;
	}
	return (str);
}
//int	main(void)
//{	
//	printf("Expected -653| Current : %s\n", ft_itoa(-653));
//	printf("Expected 156| Current : %s\n", ft_itoa(156));
//	printf("Expected : 0 | Current : %s\n", ft_itoa(-0));
//}