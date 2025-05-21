/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:22:37 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/04/29 15:36:52 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(int fd, const char *s, ...)
{
	va_list	args;
	int		var;
	int		cnt;

	if (!s)
		return (-1);
	va_start(args, s);
	var = 0;
	cnt = 0;
	while (s[var] != '\0')
	{
		if (s[var] != '%' && s[var] != '\0')
			cnt += ft_putchar_ft(s[var], fd);
		else if (s[var + 1] != '\0')
		{
			var++;
			cnt += ft_check_char(&s[var], args, fd);
		}
		else
			cnt += ft_putchar_ft('%', fd);
		var++;
	}
	va_end(args);
	return (cnt);
}

int	ft_check_char(const char *s, va_list args, int fd)
{
	int	cnt;

	cnt = 0;
	if (*s == 'c')
		cnt += ft_putchar_ft(va_arg(args, int), fd);
	else if (*s == 's')
		cnt += ft_putstr_ft(va_arg(args, char *), fd);
	else if (*s == 'p')
		cnt += ft_putptr_ft(va_arg(args, void *), fd, LC_HEX, 16);
	else if (*s == 'd' || *s == 'i')
		cnt += ft_putnbr_base_ft(va_arg(args, int), fd, DEC, 10);
	else if (*s == 'u')
		cnt += ft_putunbr_base_ft(va_arg(args, unsigned), fd, DEC, 10);
	else if (*s == 'x')
		cnt += ft_putunbr_base_ft(va_arg(args, unsigned), fd, LC_HEX, 16);
	else if (*s == 'X')
		cnt += ft_putunbr_base_ft(va_arg(args, unsigned), fd, UP_HEX, 16);
	else if (*s == '%')
		cnt += ft_putchar_ft('%', 1);
	else
	{
		cnt += ft_putchar_ft('%', fd);
		cnt += ft_putchar_ft(*s, fd);
	}
	return (cnt);
}
