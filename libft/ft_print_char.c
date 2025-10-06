/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:12:11 by adimas-d          #+#    #+#             */
/*   Updated: 2023/07/17 15:22:00 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char character, t_flg *flg1)
{
	int	printed;

	printed = 0;
	if (flg1->minus == 0)
	{
		while (flg1->width > 1)
		{
			printed++;
			ft_putchar_fd(' ', 1);
			flg1->width--;
		}
		printed += write(1, &character, 1);
	}
	else
	{
		printed += write(1, &character, 1);
		while (flg1->width > 1)
		{
			printed++;
			ft_putchar_fd(' ', 1);
			flg1->width--;
		}
	}
	return (printed);
}
