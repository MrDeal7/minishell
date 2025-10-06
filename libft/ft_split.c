/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:30:24 by adimas-d          #+#    #+#             */
/*   Updated: 2023/11/24 17:46:25 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	string_count(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
		{
			str++;
			continue ;
		}
		count++;
		while (*str != c && *str)
			str++;
	}
	return (count);
}

void	strings_content(char **split, char *str, char c)
{
	int	i;
	int	sub_str_index;
	int	string_index;

	i = 0;
	string_index = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		sub_str_index = i;
		while (str[i] != c && str[i])
			i++;
		split[string_index] = malloc(i - sub_str_index + 1);
		ft_strlcpy(split[string_index], str + sub_str_index,
			i - sub_str_index + 1);
		string_index++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		sub_string_count;
	char	**split;
	char	*s_copy;

	s_copy = (char *)s;
	sub_string_count = string_count(s_copy, c);
	split = malloc(sizeof(char *) * (sub_string_count + 1));
	if (!split)
		return (0);
	split[sub_string_count] = 0;
	strings_content(split, s_copy, c);
	return (split);
}
