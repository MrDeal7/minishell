/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:05:54 by adimas-d          #+#    #+#             */
/*   Updated: 2023/07/17 15:22:42 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long long number, char *base, t_flg *flg1)
{
	int					res;
	unsigned long long	base_size;

	base_size = ft_strlen(base);
	res = 0;
	if (number < base_size)
	{
		ft_putchar_fd(base[number], 1);
		return (1);
	}
	else
	{
		res += ft_print_ptr((number / base_size), base, flg1);
		res += ft_print_ptr((number % base_size), base, flg1);
	}
	return (res);
}

int	ft_space_adding(unsigned long long addr, t_flg *flg1)
{
	int	size;
	int	printed;

	size = 1;
	printed = 0;
	while (addr > 16)
	{
		addr = addr / 16;
		size++;
	}
	flg1->width = flg1->width - size - 2;
	while (flg1->width > 0)
	{
		ft_putchar_fd(' ', 1);
		printed++;
		flg1->width--;
	}
	return (printed);
}

int	ft_print_addr(unsigned long long addr, t_flg *flg1)
{
	int	printed;

	printed = 0;
	if (addr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		printed = 5;
	}
	else
	{
		if (flg1->minus == 0)
			printed += ft_space_adding(addr, flg1);
		ft_putstr_fd("0x", 1);
		printed += 2;
		printed += ft_print_ptr(addr, "0123456789abcdef", flg1);
		if (flg1->minus == 1)
			printed += ft_space_adding(addr, flg1);
	}
	return (printed);
}
