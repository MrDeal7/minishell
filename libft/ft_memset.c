/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:20 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:53 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buffer, int ch, size_t count)
{
	size_t	i;
	char	*b;

	b = (char *)buffer;
	i = 0;
	while (i < count)
	{
		b[i] = ch;
		i++;
	}
	return (buffer);
}
