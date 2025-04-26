/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:27:43 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/21 14:42:16 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long int	b;

	b = n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (b < 0)
	{
		write(fd, "-", 1);
		b = -b;
	}
	if (b > 9)
	{
		ft_putnbr_fd(b / 10, fd);
		ft_putnbr_fd(b % 10, fd);
	}
	else
	{
		c = b + '0';
		write (fd, &c, 1);
	}
}
