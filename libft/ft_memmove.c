/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:55:05 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:54 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *to, const void *from, size_t count)
{
	char	*to2;
	char	*from2;

	to2 = (char *)to;
	from2 = (char *)from;
	if (!from && !to)
		return (NULL);
	else if (to > from)
	{
		while (count-- > 0)
			to2[count] = from2[count];
	}
	else
		ft_memcpy(to, from, count);
	return (to);
}
