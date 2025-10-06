/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:21:49 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/31 20:16:35 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_special_strlcpy(char **to, char *from, int *str_i, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (from[i] && i <= size)
	{
		if (from[i] == D_QUOTE)
		{
			while (from[++i] && from[i] != D_QUOTE)
				to[*str_i][j++] = from[i];
			i++;
		}
		else if (from[i] == QUOTE)
		{
			while (from[++i] && from[i] != QUOTE)
				to[*str_i][j++] = from[i];
			i++;
		}
		else if (from[i] == SPACES || from[i] == TABS)
			i++;
		else
			to[*str_i][j++] = from[i++];
	}
}

int	string_counter(char *str)
{
	char	*temp;
	int		count;

	count = 1;
	if (!str)
		return (count);
	temp = str;
	while (*temp)
	{
		if (*temp == D_QUOTE)
			temp = ft_ignore_while_not(temp, D_QUOTE);
		else if (*temp == QUOTE)
			temp = ft_ignore_while_not(temp, QUOTE);
		else if (*temp == SPACES || *temp == TABS)
		{
			temp = ft_skip_spaces(temp) - 1;
			count++;
		}
		temp++;
	}
	return (count);
}

void	ft_strlcpy_w_quotes_helper(char *to, char *from, int *i, int *j)
{
	int	i2;
	int	j2;

	i2 = *i;
	j2 = *j;
	to[j2++] = from[i2++];
	while (from[i2] && from[i2] != D_QUOTE)
		to[j2++] = from[i2++];
	to[j2++] = from[i2++];
	*i = i2;
	*j = j2;
}

void	ft_strlcpy_w_quotes(char **to, char *from, int *str_i, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (from[i] && i <= size)
	{
		if (from[i] == D_QUOTE)
			ft_strlcpy_w_quotes_helper(to[*str_i], from, &i, &j);
		else if (from[i] == QUOTE)
		{
			to[*str_i][j++] = from[i++];
			while (from[i] && from[i] != QUOTE)
				to[*str_i][j++] = from[i++];
			to[*str_i][j++] = from[i++];
		}
		else if (from[i] == SPACES || from[i] == TABS)
			i++;
		else
			to[*str_i][j++] = from[i++];
	}
}

int	ft_isvalid_export(char *line, int i)
{
	bool	char_flag;

	char_flag = false;
	while (line[i] && line[i] != '=')
	{
		if (char_flag == 0 && ft_isalpha(line[i]))
			char_flag = true;
		if (!ft_isalnum(line[i]) && line[i] != '_')
			return (0);
		i++;
	}
	if (char_flag)
		return (1);
	return (0);
}
