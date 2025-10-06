/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:53 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/31 21:13:49 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redirects(char *line, int redirect_count)
{
	while (*line)
	{
		if (*line == D_QUOTE)
			line = ft_ignore_while_not(line, D_QUOTE);
		else if (*line == QUOTE)
			line = ft_ignore_while_not(line, QUOTE);
		else if (*line == RD_IN)
		{
			if (line[1] && line[1] == RD_IN)
				line++;
			else
				redirect_count++;
		}
		else if (*line == RD_OUT)
		{
			if (line[1] && line[1] == RD_OUT)
				line++;
			else
				redirect_count++;
		}
		line++;
	}
	return (redirect_count);
}

int	ft_count_apends(char *line, int apend_count)
{
	while (*line)
	{
		if (*line == D_QUOTE)
			line = ft_ignore_while_not(line, D_QUOTE);
		else if (*line == QUOTE)
			line = ft_ignore_while_not(line, QUOTE);
		else if (*line == RD_IN)
		{
			if (line[1] && line[1] == RD_IN)
			{
				apend_count++;
				line++;
			}
		}
		else if (*line == RD_OUT)
		{
			if (line[1] && line[1] == RD_OUT)
			{
				apend_count++;
				line++;
			}
		}
		line++;
	}
	return (apend_count);
}

int	ft_count_pipes(t_args *args, char *line)
{
	int	pipe_counter;

	pipe_counter = 0;
	while (!args->error && *line)
	{
		if (*line == D_QUOTE)
			line = ft_ignore_while_not(line, D_QUOTE);
		else if (*line == QUOTE)
			line = ft_ignore_while_not(line, QUOTE);
		else if (ft_is_pipe(line))
			pipe_counter++;
		line++;
	}
	return (pipe_counter);
}

void	ft_count_pipe_redirect(t_args *args, char *line)
{
	args->pipe_count = ft_count_pipes(args, line);
	args->redirect_count = ft_count_redirects(line, 0);
	args->apend_count = ft_count_apends(line, 0);
}

char	*ft_put_spaces(char *line, int size, int j)
{
	char	*temp;
	char	*new;

	if (!line)
		return (NULL);
	temp = line;
	new = ft_calloc(size + 1, sizeof(char));
	while (*temp)
	{
		if (*temp == D_QUOTE)
			temp = ft_put_spaces_helper(new, temp, &j);
		else if (*temp == QUOTE)
			temp = ft_put_spaces_helper2(new, temp, &j);
		else if (*temp == PIPE || *temp == RD_IN || *temp == RD_OUT)
			temp = ft_put_spaces2(new, temp, &j);
		else
		{
			new[j++] = *temp;
			temp++;
		}
	}
	free(line);
	return (new);
}
