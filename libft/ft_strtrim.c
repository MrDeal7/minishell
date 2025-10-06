/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:04:02 by adimas-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:34 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_trim(char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

unsigned int	ft_start(const char *s1, const char *set)
{
	int				i;
	unsigned int	start;

	i = 0;
	start = 0;
	while (s1[i])
	{
		if (ft_trim(s1[i], set))
			start++;
		else
			break ;
		i++;
	}
	return (start);
}

size_t	ft_end(const char *s1, const char *set, size_t len)
{
	size_t	end;

	end = 0;
	while (s1[len])
	{
		if (ft_trim(s1[len], set))
		{
			end++;
			len--;
		}
		else
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			len;
	char			*newstr;
	unsigned int	start;
	size_t			end;
	size_t			size;

	len = ft_strlen(s1);
	start = ft_start(s1, set);
	end = ft_end(s1, set, len - 1);
	size = len - start - end;
	newstr = ft_substr(s1, start, size);
	return (newstr);
}
