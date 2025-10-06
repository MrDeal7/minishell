/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:16:16 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 16:13:29 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sz_in_quotes(char *str, char c)
{
	int	i;

	i = 0;
	if (*str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	if (str[i - 1] && str[i - 1] == c)
		i--;
	return (i);
}

char	*ft_skip_spaces(char *str)
{
	char	*temp;

	if (!str)
		return (NULL);
	temp = str;
	while (*temp && (*temp == ' ' || *temp == '\t'))
		temp++;
	return (temp);
}

char	*ft_jump_rdir(char *str)
{
	char	*temp;

	if (!str)
		return (NULL);
	temp = str;
	while (*temp == RD_IN || *temp == RD_OUT)
		temp++;
	while (*temp != SPACES)
		temp++;
	return (temp);
}

char	**ft_dup_arr(char **arr)
{
	char	**temp;
	int		size;
	int		i;

	if (!arr && !*arr)
		return (NULL);
	size = 0;
	i = -1;
	while (arr[size])
		size++;
	temp = ft_calloc(size + 1, sizeof(char *));
	while (++i <= size && arr[i])
		temp[i] = ft_strdup(arr[i]);
	return (temp);
}

int	ft_copy_until(char *to, char *from, char c, int j)
{
	while (*from && *from != c)
	{
		to[j++] = *from;
		from++;
	}
	to[j++] = *from;
	from++;
	return (j);
}
