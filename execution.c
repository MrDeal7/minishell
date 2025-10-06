/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:56:55 by divalent          #+#    #+#             */
/*   Updated: 2024/11/01 22:29:08 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *com, char **env)
{
	char	**paths;
	char	*temp;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!(*env) || ft_strncmp(*env, "PATH=", 5) != 0)
		return (NULL);
	paths = ft_split((*env + 5), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		line = ft_strjoin(temp, com);
		free(temp);
		if (access(line, X_OK) == 0)
			return (free_array(paths), line);
		free(line);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*handle_command(t_command *cmd, char **envp)
{
	char	*path;

	if (!cmd->args[0][0])
		return (NULL);
	if (access(cmd->args[0], X_OK) == 0
		&& cmd->args[0][0] == '.' && cmd->args[0][1] == '.'
		&& cmd->args[0][2] == '/')
		return (cmd->args[0]);
	if ((cmd->args[0][0] == '.' && cmd->args[0][1] == '.')
		|| (cmd->args[0][0] == '.' && cmd->args[0][1] == '\0'))
		return (NULL);
	if (access(cmd->args[0], X_OK) == 0
		&& ((cmd->args[0][0] == '.' && cmd->args[0][1] == '/')
		|| cmd->args[0][0] == '/'))
		return (cmd->args[0]);
	path = find_path(cmd->args[0], envp);
	if (path == NULL)
		if (access(cmd->args[0], F_OK) == 0
			&& access(cmd->args[0], X_OK) != 0)
			if ((cmd->args[0][0] == '.' && cmd->args[0][1] == '/')
			|| cmd->args[0][0] == '/')
				return (cmd->args[0]);
	return (path);
}

void	set_fds(int input, int output)
{
	if (input != STDIN_FILENO)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			perror("");
	}
	if (output != STDOUT_FILENO)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
			perror("");
	}
}

void	execution(t_command *cmd, char **envp, t_args *args)
{
	char	*path;
	int		exit_code;

	set_fds(cmd->input, cmd->output);
	close_all_fds();
	path = handle_command(cmd, envp);
	if (path)
		if (execve(path, cmd->args, envp) == -1)
			perror("");
	if (!path)
		exit_code = 127;
	else if (path[0] == '\0')
		exit_code = 0;
	else
		exit_code = 126;
	if (!path)
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	if (!path)
		write(2, ": no such file or directory\n", 29);
	free_children(args, cmd);
	exit(exit_code);
}

void	built_in_execution(t_args *args, t_command *cmd,
							t_code built_in)
{
	args->exit_code = 0;
	if (cmd->ex == 1)
		set_fds(0, cmd->output);
	if (built_in == PWD)
		ft_pwd();
	else if (built_in == ECHO)
		ft_echo(cmd->args, cmd->output);
	else if (built_in == UNSET)
		ft_unset(args, cmd);
	else if (built_in == EXPORT)
		ft_export(args, cmd);
	else if (built_in == CD)
		ft_cd(args, cmd, cmd->output);
	else if (built_in == EXIT)
		ft_exit(args, cmd);
	else if (built_in == ENV)
		ft_env(args->env, cmd->output);
	close_all_fds();
	if (cmd->ex == 1)
	{
		free_children(args, cmd);
		exit(0);
	}
}
