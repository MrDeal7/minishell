/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:55:10 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/21 19:06:18 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int				len;
	unsigned char	c;
	char			*s;

	s = (char *)str;
	len = ft_strlen(s);
	c = ch;
	while (len > 0)
	{
		if (s[len] == c)
			return (&s[len]);
		len--;
	}
	if (s[len] == c)
		return (&s[len]);
	return (NULL);
}
