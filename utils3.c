/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:17:02 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/29 20:38:53 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cpy_rdir_and_putspaces(char *to, char *from, char c, int j)
{
	(void)c;
	to[j++] = SPACES;
	to[j++] = *from;
	from++;
	if (*from && (*from == RD_IN || *from == RD_OUT))
	{
		to[j++] = *from;
		from++;
	}
	to[j++] = SPACES;
	return (j);
}

char	*ft_jump_char(char *str, char c)
{
	if (c == RD_IN || c == RD_OUT)
		str++;
	if (*str && *str == c)
		str++;
	return (str);
}

int	ft_cpy_pipe_and_putspaces(char *to, char *from, int j)
{
	to[j++] = SPACES;
	to[j++] = *from;
	from++;
	to[j++] = SPACES;
	return (j);
}

int	ft_is_rd(char *str, char c)
{
	if (!str)
		return (0);
	if (c == RD_IN)
	{
		str++;
		if (*str == RD_IN)
			return (2);
	}
	if (c == RD_OUT)
	{
		str++;
		if (*str == RD_IN)
			return (2);
	}
	return (1);
}

int	ft_is_two_rdout(char *str)
{
	if (!str)
		return (0);
	str++;
	if (*str == RD_OUT)
		return (2);
	return (1);
}
