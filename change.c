/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:01:33 by divalent          #+#    #+#             */
/*   Updated: 2024/10/23 16:28:00 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_next_in(t_command *cmd, int new_fd)
{
	if (cmd->next && cmd->next->input != STDIN_FILENO)
		close(cmd->next->input);
	if (cmd->next)
		cmd->next->input = new_fd;
}

void	change_in(t_command *cmd, int new_fd)
{
	if (cmd->input != STDIN_FILENO)
		close(cmd->input);
	cmd->input = new_fd;
}

void	change_out(t_command *cmd, int new_fd)
{
	if (cmd->output != STDOUT_FILENO)
		close(cmd->output);
	cmd->output = new_fd;
}
