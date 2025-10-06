/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:34:17 by divalent          #+#    #+#             */
/*   Updated: 2024/10/29 12:17:40 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str_to_srch, char *str_to_cmp)
{
	int	n;

	n = 0;
	while (str_to_srch && str_to_cmp && (str_to_srch[n] || str_to_cmp[n]))
	{
		if (str_to_srch[n] != str_to_cmp[n])
		{
			return (str_to_srch[n] - str_to_cmp[n]);
		}
		n++;
	}
	return (0);
}
