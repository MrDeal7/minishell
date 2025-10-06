/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_verify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:52:06 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 15:33:34 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_wrong_nbr_of_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == QUOTE)
		{
			i++;
			while (line[i] && line[i] != QUOTE)
				i++;
			if (!line[i])
				return (true);
		}
		else if (line[i] == D_QUOTE)
		{
			i++;
			while (line[i] && line[i] != D_QUOTE)
				i++;
			if (!line[i])
				return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_wrong_rdir(char **args, int i)
{
	if (args[i + 1] && args[i + 1][0] && args[i + 1][0] != '\0')
		return (false);
	return (true);
}

bool	ft_pipe_sytax(char **args, int i)
{
	if (i == 0)
		return (true);
	if (args[i - 1] && args[i + 1] && args[i - 1][0] && args[i + 1][0]
		&& args[i - 1][0] != PIPE && args[i + 1][0] != PIPE)
		return (false);
	return (true);
}

bool	ft_not_alowed_char(char *arg)
{
	char	*temp;

	temp = arg;
	while (temp && *temp)
	{
		if (*temp == QUOTE || *temp == D_QUOTE)
			temp = ft_ignore_while_not(temp, *temp);
		else if (*temp == '(' || *temp == ')' || *temp == '[' || *temp == ']' \
			|| *temp == '{' || *temp == '}' || *temp == ';' || *temp == '&')
			return (true);
		temp++;
	}
	return (false);
}

void	ft_syntax(t_args *args, char *line)
{
	int		i;
	char	**temp;

	temp = ft_split_args(line, 1);
	i = 0;
	args->error = ft_wrong_nbr_of_quotes(line);
	if (!temp || !temp[0])
	{
		args->error = true;
		return ;
	}
	while (!args->error && temp[i])
	{
		if (temp[i][0] == RD_IN)
			args->error = ft_wrong_rdir(temp, i);
		else if (temp[i][0] == RD_OUT)
			args->error = ft_wrong_rdir(temp, i);
		else if (temp[i][0] == PIPE)
			args->error = ft_pipe_sytax(temp, i);
		else
			args->error = ft_not_alowed_char(temp[i]);
		i++;
	}
	ft_free_array(temp);
}
