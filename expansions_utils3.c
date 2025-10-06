/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:25:34 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:29:36 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_for_expansions_helper(t_args *args, char *line, char *temp, \
			int *expan_sz)
{
	if (*line == DOLLAR && *(line + 1) && ft_good_if(line))
	{
		if (*(line + 1) == DOLLAR)
		{
			temp = ft_put_pid();
			*expan_sz += (ft_strlen(temp) + 1);
			free(temp);
		}
		else if (*(line + 1) == QUESTION)
		{
			temp = ft_itoa(args->exit_code);
			*expan_sz += ft_strlen(temp);
			free(temp);
		}
		else
			*expan_sz += dollar_expansion_size(args, line);
		line++;
	}
}

char	*space_for_expansions(t_args *args, char *line, int line_sz, \
			int expan_sz)
{
	char	*new;
	char	*temp;

	temp = NULL;
	while (*line)
	{
		if (*line == D_QUOTE)
		{
			expan_sz += expansion_size_in_d_quotes(args, line);
			line++;
			while (*line && *line != D_QUOTE)
				line++;
		}
		else if (*line == QUOTE)
		{
			line++;
			while (*line && *line != QUOTE)
				line++;
		}
		else if (*line == DOLLAR)
			space_for_expansions_helper(args, line, temp, &expan_sz);
		line++;
	}
	new = ft_calloc((line_sz + expan_sz) + 1, 1);
	return (new);
}

int	ft_size_of_pid(void)
{
	char	*pid;
	int		size;

	pid = ft_put_pid();
	size = ft_strlen(pid);
	free(pid);
	return (size);
}

int	ft_size_of_exitcode(t_args *args)
{
	char	*exit;
	int		size;

	exit = ft_itoa(args->exit_code);
	size = ft_strlen(exit);
	free(exit);
	return (size);
}
