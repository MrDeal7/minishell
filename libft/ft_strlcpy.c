/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:53:45 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:39 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *to, const char *from, size_t size)
{
	size_t	src_len;
	char	*src;
	size_t	i;

	i = 0;
	src = (char *)from;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size)
	{
		while (src[i] && i < size - 1)
		{
			to[i] = src[i];
			i++;
		}
	}
	to[i] = 0;
	return (src_len);
}
