/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:53:09 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:44 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int				i;
	unsigned char	c;
	char			*st;

	i = 0;
	c = ch;
	st = (char *)str;
	while (st[i])
	{
		if (st[i] == c)
			return (&st[i]);
		i++;
	}
	if (st[i] == c)
		return (&st[i]);
	return (NULL);
}
