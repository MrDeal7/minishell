/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:52:50 by divalent          #+#    #+#             */
/*   Updated: 2024/11/01 22:32:55 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	close_all_fds(void)
{
	int	i;

	i = 3;
	while (i < FOPEN_MAX)
	{
		close(i);
		i++;
	}
}

void	here_doc2(t_args *args, t_command *cmd, t_pipes *pipes, char *limiter)
{
	int	i;

	i = 0;
	while (1)
	{
		signal_handler(HERE_DOC);
		cmd->temp = readline("> ");
		if (!cmd->temp)
			break ;
		if (ft_strncmp(cmd->temp, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_putendl_fd(cmd->temp, pipes->here_doc_pipe[1]);
		free(cmd->temp);
		i++;
	}
	free(cmd->temp);
	free_children(args, cmd);
	close_all_fds();
	exit (0);
}

int	here_doc(t_args *args, t_command *cmd, t_pipes *pipes, char *limiter)
{
	pid_t	pid;

	if (pipe(pipes->here_doc_pipe) == -1)
		perror("");
	pid = fork();
	if (pid == 0)
		here_doc2(args, cmd, pipes, limiter);
	close(pipes->here_doc_pipe[1]);
	change_in(cmd, pipes->here_doc_pipe[0]);
	waitpid(pid, &args->exit_code, 0);
	if (WIFEXITED(args->exit_code))
		return (WEXITSTATUS(args->exit_code));
	return (0);
}

void	change_flag(t_command **cmd)
{
	t_command	*temp;

	temp = *cmd;
	if (!temp)
		return ;
	while (temp)
	{
		temp->ex = 1;
		temp = temp->next;
	}
}
