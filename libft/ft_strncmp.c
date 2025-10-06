/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:45:11 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/29 16:14:45 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t count)
{
	size_t			i;
	unsigned char	size1;
	unsigned char	size2;
	const char		*s1;
	const char		*s2;

	if (!str1 || !str2)
		return (0);
	s1 = str1;
	s2 = str2;
	i = 0;
	if (count == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0 && i < (count - 1))
		i++;
	size1 = str1[i];
	size2 = str2[i];
	return (size1 - size2);
}
