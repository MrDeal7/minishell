/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_nbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:06:03 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 18:14:41 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uns_nbr_size(unsigned int number)
{
	int	counter;

	counter = 1;
	while (number > 9)
	{
		number = number / 10;
		counter++;
	}
	return (counter);
}

int	ft_add_padding_uns(unsigned int num, t_flg *flg1)
{
	int	size;
	int	counter;

	size = ft_uns_nbr_size(num);
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

int	ft_uns_nbr_write(unsigned int num, char *base, t_flg *flg1)
{
	int	res;
	int	base_size;

	base_size = ft_strlen(base);
	res = 0;
	if (num / base_size > 0)
		res = ft_uns_nbr_write(num / base_size, base, flg1);
	res++;
	ft_putchar_fd(base[num % base_size], 1);
	return (res);
}

int	ft_uns_nbr_precision(unsigned int num, t_flg *flg1)
{
	int	size;
	int	counter;

	size = ft_uns_nbr_size(num);
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

int	ft_print_uns_nbr(unsigned int num, char *base, t_flg *flg1)
{
	int	res;

	res = 0;
	if (flg1->zero > 0)
		res = ft_add_padding_uns(num, flg1);
	if (flg1->minus == 0)
		res += ft_add_uns_width(num, flg1);
	if (flg1->point == 1)
		res += ft_uns_nbr_precision(num, flg1);
	res += ft_uns_nbr_write(num, base, flg1);
	if (flg1->minus == 1)
		res += ft_add_uns_width(num, flg1);
	return (res);
}
