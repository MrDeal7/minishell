/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:22:38 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:37:25 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

void	ft_convertion(char *str, long num, int len)
{
	while (num > 0)
	{
		str[len] = '0' + (num % 10);
		num /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	char	*str;

	num = n;
	len = ft_len(num);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len--] = 0;
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	ft_convertion(str, num, len);
	return (str);
}
