/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:46:17 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:41 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*new;
	char			*s1x;
	char			*s2x;

	i = 0;
	s1x = (char *)s1;
	s2x = (char *)s2;
	new = malloc(ft_strlen(s1x) + ft_strlen(s2x) + 1);
	if (!new)
		return (NULL);
	while (*s1x)
		new[i++] = *s1x++;
	while (*s2x)
		new[i++] = *s2x++;
	new[i] = 0;
	return (new);
}
