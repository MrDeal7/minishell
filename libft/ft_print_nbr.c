/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:06:03 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 18:14:29 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_nbr_padding(t_flg *flg1)
{
	int	counter;

	counter = 0;
	while (flg1->zero > 0)
	{
		if (flg1->point == true)
			ft_putchar_fd(' ', 1);
		else
			ft_putchar_fd('0', 1);
		flg1->zero--;
		counter++;
	}
	return (counter);
}

int	ft_add_padding(int num, t_flg *flg1)
{
	int	size;
	int	counter;

	size = ft_nbr_size(num);
	counter = 0;
	if (num < 0 && num != -2147483648 && flg1->point == false)
	{
		ft_putchar_fd('-', 1);
		flg1->printminus = 1;
	}
	if (flg1->zero >= flg1->precision && size <= flg1->precision)
		flg1->zero -= flg1->precision;
	if (flg1->point == false || size >= flg1->precision)
		flg1->zero -= size;
	if (flg1->printminus == true && size <= flg1->precision)
		flg1->zero -= 1;
	counter += ft_put_nbr_padding(flg1);
	return (counter);
}

int	ft_print3_nbr(int number, t_flg *flg1)
{
	int	counter;

	counter = 0;
	if (flg1->point == true && flg1->precision > 0)
	{
		counter += ft_nbr_precision(number, flg1);
		if (number < 0)
			number *= -1;
	}
	ft_putnbr_fd(number, 1);
	counter += ft_nbr_size(number);
	if (flg1->minus == true)
		counter += ft_add_precision(number, flg1);
	return (counter);
}

int	ft_print2_nbr(int number, t_flg *flg1)
{
	int	counter;

	counter = 0;
	if (flg1->space == true)
	{
		if (number >= 0)
		{
			ft_putchar_fd(' ', 1);
			counter++;
		}
	}
	if (flg1->minus == false)
		counter += ft_add_precision(number, flg1);
	if (flg1->plus == true)
	{
		if (number >= 0)
		{
			ft_putchar_fd('+', 1);
			counter++;
		}
	}
	counter += ft_print3_nbr(number, flg1);
	return (counter);
}

int	ft_print_nbr(int number, t_flg *flg1)
{
	int	counter;

	counter = 0;
	if (number < 0)
		flg1->printminus = true;
	if (flg1->zero > 0 && flg1->precision < flg1->zero)
	{
		if (number < 0 && number != -2147483648)
		{
			counter = ft_add_padding(number, flg1);
			if (flg1->point == false)
			{
				number *= -1;
				counter++;
				flg1->width--;
			}
		}
		else
			counter = ft_add_padding(number, flg1);
	}
	counter += ft_print2_nbr(number, flg1);
	return (counter);
}
