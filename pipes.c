/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:27:49 by divalent          #+#    #+#             */
/*   Updated: 2024/11/01 22:22:34 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirects2(t_command *cmd, int i, int new_fd)
{
	char	*temp;

	temp = ft_strdup(cmd->redir[i]);
	if (ft_strncmp(temp, ">>", 2) == 0)
	{
		new_fd = open((temp + 3), O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (new_fd >= 0)
			change_out(cmd, new_fd);
		else
			cmd->redir_e = 1;
	}
	else if (ft_strncmp(temp, ">", 1) == 0)
	{
		new_fd = open((temp + 2), O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (new_fd >= 0)
			change_out(cmd, new_fd);
		else
			cmd->redir_e = 1;
	}
	free(temp);
}

void	check_redirects(t_args *args, t_command *cmd, t_pipes *pipes,
			t_code code)
{
	int	i;
	int	new_fd;

	i = 0;
	while (cmd->redir && cmd->redir[i] && !args->exit_code)
	{
		if (ft_strncmp(cmd->redir[i], "<<", 2) == 0)
			args->exit_code = here_doc(args, cmd, pipes, (cmd->redir[i] + 3));
		else if (ft_strncmp(cmd->redir[i], "<", 1) == 0)
		{
			new_fd = open((cmd->redir[i] + 2), O_RDONLY);
			if (new_fd >= 0)
				change_in(cmd, new_fd);
			else
				cmd->redir_e = 1;
		}
		else
			check_redirects2(cmd, i, new_fd);
		i++;
	}
	if (cmd->redir_e == 1)
		args->exit_code = 1;
	(void) code;
}

void	handle_pipes(t_pipes *pipes, t_command *cmd)
{
	static int	i;

	if (cmd->next)
	{
		if (i % 2 == 0)
		{
			if (pipe(pipes->pipe_fd) == -1)
				perror("");
			change_next_in(cmd, pipes->pipe_fd[0]);
			change_out(cmd, pipes->pipe_fd[1]);
		}
		else
		{
			if (pipe(pipes->pipe_fd_extra) == -1)
				perror("");
			change_next_in(cmd, pipes->pipe_fd_extra[0]);
			change_out(cmd, pipes->pipe_fd_extra[1]);
		}
	}
	i++;
}

void	command_handler(t_args *args, t_command *cmd, pid_t pid)
{
	t_pipes	pipes;
	t_code	built_in;

	signal_handler(IGNORE);
	built_in = check_line(cmd->args[0]);
	handle_pipes(&pipes, cmd);
	check_redirects(args, cmd, &pipes, built_in);
	if (args->exit_code == 130)
		return ;
	if (cmd->args && !cmd->args[0])
		return ;
	if (built_in != OTHER && !cmd->next && cmd->redir_e == 0)
	{
		built_in_execution(args, cmd, built_in);
		return ;
	}
	signal_handler(CHILD);
	if (cmd->redir_e == 0)
		pid = fork();
	if (pid == 0 && cmd->redir_e == 0)
		exec_caller(args, cmd, built_in);
	if (!cmd->next)
		waitpid(pid, &args->exit_code, 0);
	if (WIFEXITED(args->exit_code))
		args->exit_code = WEXITSTATUS(args->exit_code);
}

void	function_caller(t_args *args, t_command *cmd)
{
	pid_t		pid2;
	t_command	*temp;

	pid2 = -1;
	command_handler(args, cmd, -1);
	good_close(cmd);
	signal_handler(IGNORE);
	if (cmd->next)
		pid2 = fork();
	if (pid2 == 0 && cmd->next)
	{
		temp = cmd->next;
		ft_clear_cmd(cmd);
		function_caller(args, temp);
		free_children(args, temp);
		close_all_fds();
		exit(args->exit_code);
	}
	if (pid2 > 0)
		waitpid(pid2, &args->exit_code, 0);
	if (WIFEXITED(args->exit_code))
		args->exit_code = WEXITSTATUS(args->exit_code);
}
