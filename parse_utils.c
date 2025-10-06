/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:40:02 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 17:44:48 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_command_lst_start(char	*line)
{
	t_command	*new;

	new = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redir = NULL;
	new->line = line;
	new->input = 0;
	new->output = 1;
	new->next = NULL;
	new->ex = 0;
	new->redir_e = 0;
	new->temp = NULL;
	return (new);
}

void	ft_cmd_lst_add_back(t_command **lst, t_command *new)
{
	t_command	*temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_build_cmd_lst(t_args *args, t_command **cmd)
{
	t_command	*temp;
	int			i;

	i = 0;
	while (args->argv[i] && args->argv[i][0])
	{
		temp = ft_command_lst_start(args->argv[i]);
		temp->line = args->argv[i];
		if (!temp)
			error_exit("Unable to creat command list");
		else if (!*cmd)
			*cmd = temp;
		else
			ft_cmd_lst_add_back(cmd, temp);
		i++;
	}
}

int	ft_need_spaces(char *line, int i)
{
	if (!line[i])
		return (0);
	if (i == 0)
		return (2);
	if (line[i - 1] && (line[i - 1] != SPACES && line[i - 1] != TABS \
		&& line[i - 1] != line[i]) \
		&& line[i + 1] && (line[i + 1] != SPACES \
		&& line[i + 1] != TABS && line[i + 1] != line[i]))
		return (2);
	if (line[i - 1] && (line[i - 1] != SPACES && line[i - 1] != TABS \
			&& line[i - 1] != line[i]))
		return (1);
	if (line[i + 1] && (line[i + 1] != SPACES && line[i + 1] != TABS \
		&& line[i + 1] != line[i]))
		return (1);
	return (0);
}

char	*ft_put_spaces2(char *new, char *line, int *j)
{
	char	*temp;

	temp = line;
	if (*temp == QUOTE)
	{
		new[(*j)++] = QUOTE;
		*j = ft_copy_until(new, temp + 1, QUOTE, *j);
		temp = ft_ignore_while_not(temp, QUOTE) + 1;
	}
	else if (*temp == PIPE)
	{
		*j = ft_cpy_pipe_and_putspaces(new, temp, *j);
		temp = ft_jump_char(temp, PIPE);
	}
	else if (*temp == RD_IN)
	{
		*j = ft_cpy_rdir_and_putspaces(new, temp, RD_IN, *j);
		temp = ft_jump_char(temp, RD_IN);
	}
	else if (*line == RD_OUT)
	{
		*j = ft_cpy_rdir_and_putspaces(new, temp, RD_OUT, *j);
		temp = ft_jump_char(temp, RD_OUT);
	}
	return (temp);
}
