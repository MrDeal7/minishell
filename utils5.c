/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:14:49 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/29 17:48:32 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_to_array(char **array, char *new_line)
{
	char	**new_array;
	int		i;

	new_array = ft_calloc(ft_array_sz(array) + 2, sizeof(char *));
	if (!new_array)
		error_exit("Error trying to alloc memory for add to an array\n");
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = ft_strdup(new_line);
	ft_free_array(array);
	return (new_array);
}

char	*ft_ignore_while_not(char *str, char c)
{
	if (*str == c)
		str++;
	while (*str && *str != c)
		str++;
	return (str);
}

int	ft_is_alpha_blank_quote_s(char c)
{
	if (ft_isalpha(c) || c == '\t' || c == ' ' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ft_is_alpha_blank_dollar_quote_s(char c)
{
	if (ft_isalpha(c) || c == '\t' || c == ' ' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ft_is_pipe(char *str)
{
	if (str[1] && *str == '|' && ft_is_alpha_blank_dollar_quote_s(str[1]))
		return (1);
	return (0);
}
