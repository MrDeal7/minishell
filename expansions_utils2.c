/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:48:11 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:29:23 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion_size_in_d_quotes(t_args *args, char *line)
{
	int		expan_sz;

	expan_sz = 0;
	if (*line == D_QUOTE)
		line++;
	while (*line && *line != D_QUOTE)
	{
		if (*line == DOLLAR && *(line + 1) && *(line + 1) == DOLLAR)
			expan_sz += ft_size_of_pid();
		else if (*line == DOLLAR && *(line + 1) && *(line + 1) == QUESTION)
			expan_sz += ft_size_of_exitcode(args);
		else if (*line == DOLLAR)
			expan_sz += dollar_expansion_size(args, line);
		line++;
	}
	return (expan_sz);
}
//acrescentar as expancoes de $$ e de $?

int	dollar_expansion(t_args *args, char *line, char *new_str, int j)
{
	int		i;
	int		size;
	char	*temp;

	i = 1;
	size = 1;
	while (line[i])
	{
		if (line[i] == '_' || ft_isalnum(line[i]))
			size++;
		else
			break ;
		i++;
	}
	temp = env_search(args, line, size);
	if (!temp)
		return (j);
	while (*temp)
	{
		new_str[j] = *temp;
		j++;
		temp++;
	}
	return (j);
}

int	ft_pid_expand(char *new_str, int j)
{
	char	*pid;
	int		i;

	pid = ft_put_pid();
	i = 0;
	while (pid[i])
	{
		new_str[j++] = pid[i++];
	}
	free(pid);
	return (j);
}

int	ft_put_exitcode(t_args *args, char *new_str, int j)
{
	char	*exit;
	int		i;

	i = 0;
	exit = ft_itoa(args->exit_code);
	while (exit[i])
	{
		new_str[j++] = exit[i];
		i++;
	}
	free(exit);
	return (j);
}

char	*ft_dont_expand(char *line, char *new_str, int *j)
{
	if (*line == RD_IN)
		new_str[(*j)++] = *line;
	line++;
	if (*line == RD_IN)
		new_str[(*j)++] = *line;
	line++;
	if (*line == SPACES || *line == TABS)
		new_str[(*j)++] = SPACES;
	line++;
	while (*line == SPACES || *line == TABS)
		line++;
	while (*line && ft_isprint(*line) && *line != SPACES && *line != TABS)
	{
		new_str[(*j)++] = *line;
		line++;
	}
	return (line);
}
