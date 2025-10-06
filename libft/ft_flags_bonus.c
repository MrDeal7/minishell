/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:52:26 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/28 17:31:57 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pads(const char **format, t_flg *flg1)
{
	int	pading;

	pading = 0;
	while (**format >= '0' && **format <= '9')
	{
		pading *= 10;
		pading += **format - '0';
		(*format)++;
	}
	flg1->zero = pading;
}

void	ft_add_space(const char **format, t_flg *flg1)
{
	int	printlimit;

	printlimit = 0;
	while (**format >= '0' && **format <= '9')
	{
		printlimit *= 10;
		printlimit += **format - '0';
		(*format)++;
	}
	flg1->printlimit = printlimit;
}

void	ft_flags3_bonus(const char **format, t_flg *flg1)
{
	while (true)
	{
		if (**format == '.')
		{
			flg1->point = true;
			(*format)++;
			ft_precision_size(format, flg1);
		}
		else
			break ;
	}
}

void	ft_flags2_bonus(const char **format, t_flg *flg1)
{
	while (true)
	{
		if (**format == '-')
		{
			flg1->minus = true;
			flg1->zero = false;
			(*format)++;
		}
		else if (**format == '+')
		{
			flg1->plus = true;
			(*format)++;
		}
		else if (**format == ' ')
		{
			flg1->space = true;
			flg1->plus = false;
			(*format)++;
			ft_add_space(format, flg1);
		}
		else if (**format == '.')
			ft_flags3_bonus(format, flg1);
		else
			break ;
	}
}

void	ft_flags1_bonus(const char **format, t_flg *flg1)
{
	while (true)
	{
		if (**format == '#')
		{
			flg1->hashtag = true;
			(*format)++;
		}
		else if (**format == '0')
		{
			(*format)++;
			if (flg1->minus == 0)
				ft_pads(format, flg1);
		}
		else if (**format == '-' || **format == '+' || \
				**format == ' ' || **format == '.')
			ft_flags2_bonus(format, flg1);
		else if (**format > '0' && **format <= '9')
			ft_width_bonus(format, flg1);
		else
			break ;
	}
}
