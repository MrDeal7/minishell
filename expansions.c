/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:43:11 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 16:05:42 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_vars_d_quotes_helper(t_args *args, char *line, \
			char *new_str, int *j)
{
	if (*line == DOLLAR && *(line + 1) && ft_good_if(line))
	{
		line++;
		if (*line == DOLLAR)
		{
			*j = ft_pid_expand(new_str, *j);
			line++;
		}
		else if (*line == QUESTION)
		{
			*j = ft_put_exitcode(args, new_str, *j);
			line++;
		}
		else if (*line == '_' || ft_isalnum(*line))
		{
			*j = dollar_expansion(args, line, new_str, *j);
			line++;
			while (*line && (*line == '_' || ft_isalnum(*line)))
				line++;
		}
	}
	else
		new_str[(*j)++] = *(line++);
	return (line);
}

char	*ft_expand_vars_d_quotes(t_args *args, char *line,
		char *new_str, int *j)
{
	int	j2;

	j2 = *j;
	if (*line == D_QUOTE)
	{
		new_str[j2++] = *line;
		line++;
	}
	while (*line && *line != D_QUOTE)
	{
		if (*line == DOLLAR)
			line = ft_expand_vars_d_quotes_helper(args, line, new_str, &j2);
		else if (*line == D_QUOTE)
		{
			new_str[j2++] = *line;
			line++;
		}
		else
		{
			new_str[j2++] = *line;
			line++;
		}
	}
	*j = j2;
	return (line);
}

char	*ft_expand_vars_quotes(char *line, char *new_str, int *j)
{
	int	j2;

	j2 = *j;
	if (*line == QUOTE)
	{
		new_str[j2++] = *line;
		line++;
	}
	while (*line && *line != QUOTE)
	{
		new_str[j2++] = *line;
		line++;
	}
	new_str[j2] = *line;
	line++;
	j2++;
	*j = j2;
	return (line);
}

char	*ft_expand_vars_helper(t_args *args, char *line, char *new_str, int *j)
{
	if (*line == DOLLAR && *(line + 1) && ft_good_if(line))
	{
		line++;
		if (*line == DOLLAR)
		{
			*j = ft_pid_expand(new_str, *j);
			line++;
		}
		else if (*line == QUESTION)
		{
			*j = ft_put_exitcode(args, new_str, *j);
			line++;
		}
		else if (*line == '_' || ft_isalnum(*line))
		{
			*j = dollar_expansion(args, line, new_str, *j);
			line++;
			while (*line && (*line == '_' || ft_isalnum(*line)))
				line++;
		}
	}
	else
		new_str[(*j)++] = *(line++);
	return (line);
}

char	*ft_expand_vars(t_args *args, char *line)
{
	int		j;
	char	*new_str;

	j = 0;
	new_str = space_for_expansions(args, line, ft_strlen(line), 0);
	while (*line)
	{
		if (*line && *(line + 1) && *(line) == RD_IN && *(line + 1) == RD_IN)
			line = ft_dont_expand(line, new_str, &j);
		if (*line == D_QUOTE)
			line = ft_expand_vars_d_quotes(args, line, new_str, &j);
		else if (*line == QUOTE)
			line = ft_expand_vars_quotes(line, new_str, &j);
		else if (*line == DOLLAR)
			line = ft_expand_vars_helper(args, line, new_str, &j);
		else
		{
			new_str[j] = *line;
			line++;
			j++;
		}
	}
	if (new_str && !new_str[0])
		new_str[0] = '\0';
	return (new_str);
}
