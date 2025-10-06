/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:45:33 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/18 12:42:40 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*buffer;
	char	*string;
	size_t	size;
	size_t	i;

	if (!str)
		return (NULL);
	string = (char *)str;
	size = ft_strlen(string);
	buffer = (char *)malloc(size + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < size)
	{
		buffer[i] = string[i];
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}
