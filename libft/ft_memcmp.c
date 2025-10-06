/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:53:26 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:55 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buffer1, const void *buffer2, size_t count)
{
	size_t			i;
	char			*buf1;
	char			*buf2;
	unsigned char	b1;
	unsigned char	b2;

	i = 0;
	buf1 = (char *)buffer1;
	buf2 = (char *)buffer2;
	if (!count)
		return (0);
	while (buf1[i] == buf2[i] && i < (count -1))
		i++;
	b1 = buf1[i];
	b2 = buf2[i];
	return (b1 - b2);
}
