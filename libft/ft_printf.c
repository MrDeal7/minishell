/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:35:04 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 18:06:08 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_percent(char percent)
{
	ft_putchar_fd(percent, 1);
	return (1);
}

int	ft_specifier(va_list args, const char *format, t_flg *flg1)
{
	int	printed;

	printed = 0;
	if (*format == 'c')
		printed += ft_print_char(va_arg(args, int), flg1);
	else if (*format == 's')
		printed += ft_str_error_check(va_arg(args, char *), flg1);
	else if (*format == 'p')
		printed += ft_print_addr(va_arg(args, size_t), flg1);
	else if (*format == 'd' || *format == 'i')
		printed += ft_print_nbr(va_arg(args, int), flg1);
	else if (*format == 'u')
		printed += ft_print_uns_nbr(va_arg(args, unsigned long),
				"0123456789", flg1);
	else if (*format == 'x')
		printed += ft_print_base(va_arg(args, unsigned int),
				"0123456789abcdef", flg1, "0x");
	else if (*format == 'X')
		printed += ft_print_base(va_arg(args, unsigned int),
				"0123456789ABCDEF", flg1, "0X");
	else if (*format == '%')
		printed += ft_print_percent('%');
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		printed;
	t_flg	flg1;

	va_start(list, format);
	printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ft_memset(&flg1, 0, sizeof(flg1));
			ft_flags1_bonus(&format, &flg1);
			printed += ft_specifier(list, format, &flg1);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			printed++;
		}
		format++;
	}
	va_end(list);
	return (printed);
}
