/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:31:27 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:37 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		n = i;
		while (big[n] == little[j] && n < len)
		{
			if (little[j + 1] == 0)
				return ((char *)&big[i]);
			j++;
			n++;
		}
		i++;
	}
	return (NULL);
}
