/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:06:06 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 21:54:31 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_padding(t_flg *flg1)
{
	int	printed;

	printed = 0;
	while (flg1->width > 0)
	{
		ft_putchar_fd(' ', 1);
		printed++;
		flg1->width--;
	}
	return (printed);
}

int	ft_print_str_minus(int size, t_flg *flg1)
{
	int	printed;

	printed = 0;
	if (flg1->point == 1 && flg1->precision <= size)
	{
		flg1->width = flg1->width - flg1->precision;
		while (flg1->width > 0)
			printed += ft_print_padding(flg1);
	}
	else
	{
		flg1->width = flg1->width - size;
		while (flg1->width > 0)
			printed += ft_print_padding(flg1);
	}
	return (printed);
}

int	ft_print_space(int size, t_flg *flg1)
{
	int	printed;

	printed = 0;
	while (flg1->printlimit > size)
	{
		ft_putchar_fd(' ', 1);
		flg1->printlimit--;
		printed++;
	}
	return (printed);
}

int	ft_print_str(char *str, t_flg *flg1)
{
	int	printed;
	int	size;

	printed = 0;
	size = ft_strlen(str);
	if (flg1->space == true)
		printed += ft_print_space(size, flg1);
	if (flg1->minus == false)
		printed += ft_print_str_minus(size, flg1);
	if (flg1->point == true)
		printed += ft_precision_print(str, flg1);
	else if (str[0] == '-' && flg1->point == true)
		return (printed);
	else
	{
		printed += size;
		ft_putstr_fd(str, 1);
	}
	if (flg1->minus == true)
		printed += ft_print_str_minus(size, flg1);
	return (printed);
}

int	ft_str_error_check(char *str, t_flg *flg1)
{
	int	printed;

	printed = 0;
	if (!str)
		str = "(null)";
	printed += ft_print_str(str, flg1);
	return (printed);
}
/*	estava a seguir ao printed = 0;

	if (!str && flg1->point == true && flg1->width == false)
		return (printed);
	else if (!str && (flg1->minus == false || flg1->minus == true))
	{
		printed += ft_print_str("(null)", flg1);
		return (printed);
	}
	else if (!str && flg1->width > 0)
	{
		printed += ft_print_padding(flg1);
		return (printed);
	}
	else */