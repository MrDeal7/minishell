/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:06:00 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 18:14:20 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_size_of_nbr(unsigned int number)
{
	int	counter;

	counter = 1;
	while (number >= 16)
	{
		number = number / 16;
		counter++;
	}
	return (counter);
}

int	ft_add_padding_nbr(unsigned int num, t_flg *flg1)
{
	int	size;
	int	counter;

	size = ft_size_of_nbr(num);
	counter = 0;
	flg1->zero -= size;
	while (flg1->zero > 0)
	{
		ft_putchar_fd('0', 1);
		flg1->zero--;
		counter++;
	}
	return (counter);
}

int	ft_print_base_nbr(unsigned int number, char *base, t_flg *flg1)
{
	int				res;
	unsigned int	base_size;

	base_size = ft_strlen(base);
	res = 0;
	if (number == 0)
	{
		ft_putnbr_fd(0, 1);
		res++;
	}
	else if (number < base_size)
	{
		ft_putchar_fd(base[number], 1);
		res++;
		return (res);
	}
	else
	{
		res = ft_print_base_nbr((number / base_size), base, flg1);
		ft_putchar_fd(base[number % base_size], 1);
		res++;
	}
	return (res);
}

int	ft_base_nbr_precision(unsigned int num, t_flg *flg1)
{
	int	size;
	int	counter;

	size = ft_size_of_nbr(num);
	counter = 0;
	flg1->precision -= size;
	while (flg1->precision > 0)
	{
		ft_putchar_fd('0', 1);
		flg1->precision--;
		counter++;
	}
	return (counter);
}

int	ft_print_base(unsigned int number, char *base, t_flg *flg1, char *hash)
{
	int	res;

	res = 0;
	if (flg1->hashtag == 1)
	{
		if (number == 0)
			;
		else
		{
			ft_putstr_fd(hash, 1);
			res += 2;
		}
	}
	if (flg1->zero > 0)
		res = ft_add_padding_nbr(number, flg1);
	if (flg1->minus == 0)
		res += ft_add_nbr_width(number, flg1);
	if (flg1->point == 1)
		res += ft_base_nbr_precision(number, flg1);
	res += ft_print_base_nbr(number, base, flg1);
	if (flg1->minus == 1)
		res += ft_add_nbr_width(number, flg1);
	return (res);
}
