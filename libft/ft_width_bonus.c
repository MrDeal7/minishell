/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:53:54 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 18:14:49 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_width_bonus(const char **format, t_flg *flg1)
{
	int	buf;

	buf = 0;
	while (**format >= '0' && **format <= '9')
	{
		buf *= 10;
		buf += **format - '0';
		(*format)++;
	}
	flg1->width = buf;
}

int	ft_add_nbr_width(unsigned int number, t_flg *flg1)
{
	int	size;
	int	printed;

	size = ft_size_of_nbr(number);
	printed = 0;
	flg1->width -= size;
	while (flg1->width > 0)
	{
		ft_putchar_fd(' ', 1);
		printed++;
		flg1->width--;
	}
	return (printed);
}

int	ft_add_uns_width(unsigned int number, t_flg *flg1)
{
	int	size;
	int	printed;

	size = ft_uns_nbr_size(number);
	printed = 0;
	flg1->width -= size;
	while (flg1->width > 0)
	{
		ft_putchar_fd(' ', 1);
		printed++;
		flg1->width--;
	}
	return (printed);
}
