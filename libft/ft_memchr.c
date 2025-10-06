/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:35:39 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:56 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buffer, int ch, size_t count)
{
	unsigned char	*buf;
	unsigned char	c;
	size_t			i;

	buf = (unsigned char *)buffer;
	c = (unsigned char)ch;
	i = 0;
	while (i < count)
	{
		if (buf[i] == c)
			return (&buf[i]);
		i++;
	}
	return (NULL);
}
