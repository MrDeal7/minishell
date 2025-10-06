/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:11:04 by adimas-d          #+#    #+#             */
/*   Updated: 2023/08/16 18:55:49 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_size(int numero)
{
	int	size;

	size = ft_strlen(ft_itoa(numero));
	return (size);
}

int	ft_nbr_size(int number)
{
	int	counter;

	counter = 1;
	if (number == -2147483648)
	{
		number -= 1;
		counter++;
	}
	if (number < 0)
	{
		number *= -1;
		counter++;
	}
	while (number > 9)
	{
		number = number / 10;
		counter++;
	}
	return (counter);
}
