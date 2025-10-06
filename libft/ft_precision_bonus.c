/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:55:17 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/28 17:31:08 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_precision_size(const char **format, t_flg *flg1)
{
	int	pading;

	pading = 0;
	while (**format >= '0' && **format <= '9')
	{
		pading *= 10;
		pading += **format - '0';
		(*format)++;
	}
	flg1->precision = pading;
}

int	ft_precision_print(char *str, t_flg *flg1)
{
	int	size;
	int	printed;
	int	i;

	i = 0;
	printed = 0;
	size = ft_strlen(str);
	if (size < flg1->precision)
		flg1->precision = size;
	if (flg1->width > flg1->precision)
		flg1->width -= flg1->precision;
	if (size == 0)
		return (printed);
	else
	{
		while (flg1->precision > 0 && str[i] != '\0')
		{
			ft_putchar_fd(str[i], 1);
			printed++;
			i++;
			flg1->precision--;
		}
	}
	return (printed);
}

int	ft_nbr_print_precision(t_flg *flg1)
{
	int	counter;

	counter = 0;
	while (flg1->precision > 0)
	{
		ft_putchar_fd('0', 1);
		flg1->precision--;
		counter++;
	}
	return (counter);
}

int	ft_nbr_precision(int number, t_flg *flg1)
{
	int	size;
	int	counter;

	size = ft_nbr_size(number);
	counter = 0;
	if (number < 0 && number != -2147483648)
	{
		ft_putchar_fd('-', 1);
		number *= -1;
		flg1->precision++;
		flg1->printminus = true;
		counter++;
	}
	if (flg1->precision >= size)
		flg1->precision -= size;
	else
		flg1->precision = 0;
	if (flg1->width >= flg1->precision && flg1->printminus == true)
		flg1->width -= flg1->precision + 1;
	else if (flg1->width >= flg1->precision)
		flg1->width -= flg1->precision;
	counter += ft_nbr_print_precision(flg1);
	return (counter);
}

int	ft_add_precision(int number, t_flg *flg1)
{
	int	size;
	int	printed;

	size = ft_nbr_size(number);
	printed = 0;
	if ((number < 0 || flg1->printminus == true) && \
	(flg1->width < 0 || flg1->precision < 0))
		flg1->width -= size + 1;
	else
		flg1->width -= size;
	if (flg1->precision > size && flg1->printminus == true)
		flg1->width -= flg1->precision - size + 1;
	else if (flg1->precision > size)
		flg1->width -= flg1->precision - size;
	while (flg1->width > 0)
	{
		ft_putchar_fd(' ', 1);
		printed++;
		flg1->width--;
	}
	return (printed);
}
