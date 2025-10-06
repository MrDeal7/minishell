/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:10:18 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:54 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t count)
{
	size_t	i;
	char	*to2;
	char	*from2;

	i = 0;
	to2 = (char *)to;
	from2 = (char *)from;
	if (!from && !to)
		return (NULL);
	while (i < count)
	{
		to2[i] = from2[i];
		i++;
	}
	return (to2);
}
