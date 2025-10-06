/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:03:53 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:40 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	char	*dest;
	char	*source;

	i = 0;
	dest = (char *)dst;
	source = (char *)src;
	dst_len = ft_strlen(dest);
	src_len = ft_strlen(source);
	if (size == 0 || size <= dst_len)
		return (src_len + size);
	while (i < size - dst_len -1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}
