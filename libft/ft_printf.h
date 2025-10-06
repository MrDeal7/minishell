/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:34:38 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 18:16:04 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include "libft.h"

typedef struct t_flg
{
	bool	hashtag;
	int		zero;
	bool	minus;
	bool	space;
	int		printlimit;
	bool	plus;
	int		width;
	bool	point;
	int		precision;
	bool	printminus;
}	t_flg;

int		ft_add_nbr_width(unsigned int number, t_flg *flg1);
int		ft_add_precision(int number, t_flg *flg1);
int		ft_add_uns_width(unsigned int number, t_flg *flg1);
void	ft_flags1_bonus(const char **format, t_flg *flg1);
int		ft_nbr_precision(int number, t_flg *flg1);
int		ft_nbr_size(int number);
void	ft_precision_bonus(const char **format, t_flg *flg1);
int		ft_precision_print(char *str, t_flg *flg1);
void	ft_precision_size(const char **format, t_flg *flg1);
int		ft_print_char(char character, t_flg *flg1);
int		ft_print_addr(unsigned long long addr, t_flg *flg1);
int		ft_print_nbr(int number, t_flg *flg1);
int		ft_print_uns_nbr(unsigned int num, char *base, t_flg *flg1);
int		ft_print_base(unsigned int number, char *base, t_flg *flg1, char *hash);
int		ft_size(int numero);
int		ft_size_of_nbr(unsigned int number);
int		ft_str_error_check(char *str, t_flg *flg1);
int		ft_uns_nbr_size(unsigned int number);
void	ft_width_bonus(const char **format, t_flg *flg1);

#endif