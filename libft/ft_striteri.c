/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:34:38 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:42 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (s != NULL && f != NULL)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			f(i, &s[i]);
			i++;
		}
	}
}
