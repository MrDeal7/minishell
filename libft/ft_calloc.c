/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:51:15 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/31 17:49:54 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*mem;
	int		memsize;

	memsize = num * size;
	if (num != 0 && memsize / num != size)
		return (NULL);
	mem = malloc (num * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, num * size);
	return (mem);
}
