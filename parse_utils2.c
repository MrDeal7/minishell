/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:04:34 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 20:42:45 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_count(t_args *args, char *str)
{
	char	*temp;
	int		str_count;

	str_count = 0;
	if (!str)
		return (str_count);
	temp = str;
	while (*temp && !args->error)
	{
		if (ft_is_pipe(temp))
			str_count++;
		else if (*temp == D_QUOTE)
			temp = ft_ignore_while_not(temp, D_QUOTE);
		else if (*temp == QUOTE)
			temp = ft_ignore_while_not(temp, QUOTE);
		temp++;
	}
	return (str_count);
}

void	ft_separated_by_pipe(t_args *args, char **splited, char *line)
{
	int		i;
	char	*temp;

	i = 0;
	temp = line;
	splited[i++] = temp;
	while (*temp && !args->error)
	{
		if (*temp == D_QUOTE)
			temp = ft_ignore_while_not(temp, D_QUOTE);
		else if (*temp == QUOTE)
			temp = ft_ignore_while_not(temp, QUOTE);
		else if (ft_is_pipe(temp))
		{
			splited[i++] = ft_skip_spaces(temp + 1);
			*temp = '\0';
		}
		temp++;
	}
}

void	ft_split_pipes(t_args *args, char *line)
{
	char	**splited;
	int		sub_str_count;

	sub_str_count = str_count(args, line);
	splited = ft_calloc(sub_str_count + 2, sizeof(char *));
	if (!splited)
		error_exit("Error trying to alloc memory for parsing\n");
	ft_separated_by_pipe(args, splited, line);
	args->argv = splited;
}

char	*ft_put_spaces_helper(char *new, char *line, int *j)
{
	char	*temp;

	temp = line;
	new[(*j)++] = D_QUOTE;
	temp++;
	*j = ft_copy_until(new, temp, D_QUOTE, *j);
	temp = ft_ignore_while_not(temp, D_QUOTE) + 1;
	return (temp);
}

char	*ft_put_spaces_helper2(char *new, char *line, int *j)
{
	char	*temp;

	temp = line;
	new[(*j)++] = QUOTE;
	temp++;
	*j = ft_copy_until(new, temp, QUOTE, *j);
	temp = ft_ignore_while_not(temp, QUOTE) + 1;
	return (temp);
}
