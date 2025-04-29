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

int	ft_printf(const char *s, ...)
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
			cnt += ft_putchar_ft(s[var], 1);
		else if (s[var + 1] != '\0')
		{
			var++;
			cnt += ft_check_char(&s[var], args);
		}
		else
			cnt += ft_putchar_ft('%', 1);
		var++;
	}
	va_end(args);
	return (cnt);
}

int	ft_check_char(const char *s, va_list args)
{
	int	cnt;

	cnt = 0;
	if (*s == 'c')
		cnt += ft_putchar_ft(va_arg(args, int), 1);
	else if (*s == 's')
		cnt += ft_putstr_ft(va_arg(args, char *), 1);
	else if (*s == 'p')
		cnt += ft_putptr_ft(va_arg(args, void *), 1, LC_HEX, 16);
	else if (*s == 'd' || *s == 'i')
		cnt += ft_putnbr_base_ft(va_arg(args, int), 1, DEC, 10);
	else if (*s == 'u')
		cnt += ft_putunbr_base_ft(va_arg(args, unsigned), 1, DEC, 10);
	else if (*s == 'x')
		cnt += ft_putunbr_base_ft(va_arg(args, unsigned), 1, LC_HEX, 16);
	else if (*s == 'X')
		cnt += ft_putunbr_base_ft(va_arg(args, unsigned), 1, UP_HEX, 16);
	else if (*s == '%')
		cnt += ft_putchar_ft('%', 1);
	else
	{
		cnt += ft_putchar_ft('%', 1);
		cnt += ft_putchar_ft(*s, 1);
	}
	return (cnt);
}
