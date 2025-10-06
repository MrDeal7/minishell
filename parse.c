/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:26:14 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 17:15:09 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_new_spaces_added(char *line, int size)
{
	int		i;
	char	*new;

	i = ft_strlen(line);
	if (size > i)
		new = ft_put_spaces(line, size, 0);
	else
		new = line;
	return (new);
}

char	*ft_add_spaces_if_needed(char *line)
{
	int		i;
	int		size;
	char	*new;

	if (!line)
		return (NULL);
	i = 0;
	size = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == D_QUOTE)
			i += ft_sz_in_quotes(line + i, D_QUOTE) + 1;
		else if (line[i] == QUOTE)
			i += ft_sz_in_quotes(line + i, QUOTE) + 1;
		else if (line[i] == PIPE)
			size += 2;
		else if (line[i] == RD_IN)
			size += 2;
		else if (line[i] == RD_OUT)
			size += 2;
		i++;
	}
	new = ft_new_spaces_added(line, size);
	return (new);
}

void	ft_parsing(t_args *args, t_command **cmd, char *line)
{
	if (!line)
	{
		cmd = NULL;
		return ;
	}
	if (spaces_handler(&line) == 1)
		return ;
	args->line = ft_add_spaces_if_needed(ft_strdup(line));
	ft_syntax(args, args->line);
	if (!args->line && !args->line)
		return ;
	ft_count_pipe_redirect(args, args->line);
	if (!args->error)
		ft_split_pipes(args, args->line);
	if (!args->error)
		ft_build_cmd_lst(args, cmd);
	if (!args->error)
		args->cmd = *cmd;
	if (!args->error)
		ft_expansions(args);
	if (!args->error)
		free(args->argv);
	if (args->error)
		error_print("Syntax Error");
}
