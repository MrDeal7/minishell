/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:20:04 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:32 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (start >= ft_strlen(s))
		sub = malloc(1);
	else if (len >= ft_strlen(s))
		sub = malloc(ft_strlen(s) - start + 1);
	else
		sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			sub[j] = s[i];
			j++;
		}
		i++;
	}
	sub[j] = 0;
	return (sub);
}
