/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:38:13 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:22:05 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_code	check_line(char *line)
{
	if (!line)
		return (OTHER);
	if (ft_strncmp(line, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(line, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(line, "unset", 6) == 0)
		return (UNSET);
	else if (ft_strncmp(line, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(line, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(line, "exit", 6) == 0)
		return (EXIT);
	else if (ft_strncmp(line, "env", 4) == 0)
		return (ENV);
	return (OTHER);
}

void	ft_start_args(t_args *args)
{
	args->exp = NULL;
	args->exit = false;
	args->exp = NULL;
	args->argv = NULL;
	args->line = NULL;
	args->cmd = NULL;
	args->apend_count = 0;
	args->redirect_count = 0;
	args->exit_code = 0;
}

void	ft_clear_cmd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->line)
		free(cmd->line);
	if (cmd->args && cmd->args[0])
		ft_free_array(cmd->args);
	else if (cmd->args)
		free(cmd->args);
	if (cmd->redir && cmd->redir[0])
		ft_free_array(cmd->redir);
	free(cmd);
}

void	ft_clear_cmd_list(t_command **cmd)
{
	t_command	*temp;

	if (!cmd && !*cmd)
		return ;
	while (*cmd)
	{
		temp = (*cmd)->next;
		ft_clear_cmd(*cmd);
		*cmd = temp;
	}
	*cmd = NULL;
}
