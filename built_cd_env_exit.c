/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_env_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:19:33 by divalent          #+#    #+#             */
/*   Updated: 2024/10/31 21:16:47 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **vars, int output)
{
	while (*vars)
		ft_putendl_fd(*vars++, output);
}

void	ft_exit(t_args *args, t_command *cmd)
{
	int	flag;

	flag = 0;
	if (cmd->args[1] && cmd->args[2])
	{
		error_print(" too many arguments\n");
		args->exit_code = 1;
		return ;
	}
	if (cmd->args[1])
		if (can_i_exit(cmd->args[1]) == 1)
			flag = 1;
	args->exit = true;
	if (cmd->args[1] && flag == 1)
		args->exit_code = ft_atoi(cmd->args[1]);
	else if (cmd->args[1] && flag == 0)
	{
		ft_putendl_fd(" numeric argument required", 2);
		args->exit_code = 2;
	}
	if (args->exit_code > 255)
		args->exit_code -= 256;
	ft_free_array(args->exp);
	ft_free_array(args->env);
}

void	ft_cd_til(t_args *args, char *line)
{
	int		i;
	char	*new;
	char	*temp;

	i = 0;
	while (ft_strncmp(args->env[i], "HOME=", 5) != 0)
		i++;
	temp = args->env[i];
	while (*temp != '=')
		temp++;
	temp++;
	line++;
	new = ft_strjoin(temp, line);
	if (!new)
		error_exit("Error trying to alloc memory for new env str\n");
	ft_update_oldpwd(args);
	chdir(new);
	args->exit_code = ft_cd_erro(errno);
	ft_update_pwd(args);
	free(new);
}

void	ft_cd_dash(t_args *args, char *line, int output)
{
	int		i;
	char	*new;

	i = 0;
	line++;
	if (*line == '\0')
	{
		while (args->env[i] && ft_strncmp(args->env[i], "OLDPWD=", 5) != 0)
			i++;
		if (args->env[i] && ft_strncmp(args->env[i], "OLDPWD=", 5) == 0)
		{
			new = ft_strtrim(args->env[i], "OLDPWD=");
			ft_update_oldpwd(args);
			chdir(new);
			args->exit_code = ft_cd_erro(errno);
			ft_putendl_fd(new, output);
			ft_update_pwd(args);
			free(new);
		}
		else
			error_print("OLDPWD not set.\n");
	}
	else
		error_print("No option is allowed");
}

void	ft_cd(t_args *args, t_command *cmd, int output)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i > 2 || !cmd->args[1])
	{
		args->exit_code = ft_cd_erro(3000);
		return ;
	}
	if (*cmd->args[1] == '~')
		ft_cd_til(args, cmd->args[1]);
	else if (*cmd->args[1] == '-')
		ft_cd_dash(args, cmd->args[1], output);
	else
	{
		ft_update_oldpwd(args);
		chdir(cmd->args[1]);
		args->exit_code = ft_cd_erro(errno);
		ft_update_pwd(args);
	}
}
