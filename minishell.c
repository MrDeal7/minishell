/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:26:47 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:29:44 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_line(t_args *args)
{
	ft_putstr_fd("exit\n", 1);
	args->exit = true;
	ft_free_array(args->exp);
	ft_free_array(args->env);
}

void	args_run(t_args *args, t_command **cmd)
{
	if (!args->error)
	{
		if (*cmd && (((*cmd)->args && (*cmd)->args[0])
				|| ((*cmd)->redir && (*cmd)->redir[0])))
		{
			if ((*cmd)->next)
				change_flag(cmd);
			args->exit_code = 0;
			function_caller(args, *cmd);
			close_all_fds();
			while (waitpid(-1, NULL, 0) > 0)
				;
		}
		if (args->exit_code > 255)
			args->exit_code -= 256;
		if (cmd)
			ft_clear_cmd_list(cmd);
	}
}

void	minishell(t_args *args, t_command **cmd, char *line, int flag)
{
	while (args->exit == false)
	{
		signal_handler(PARENT);
		args->error = false;
		line = readline(PROMPT);
		if (!line)
		{
			no_line(args);
			break ;
		}
		if (*line != '\0')
		{
			add_history(line);
			ft_parsing(args, cmd, line);
			if (flag++ == 0)
				ft_new_export_vars(args);
			free(args->line);
			get_that_saved(args);
			args_run(args, cmd);
			if (line)
				free(line);
		}
		else
			free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_args		args;
	char		*line;
	t_command	*cmd;
	int			flag;

	(void)av;
	cmd = NULL;
	flag = 0;
	line = NULL;
	if (ac == 1)
	{
		args.env = init_envp(envp);
		ft_start_args(&args);
		ft_start_exitcode(&args);
		minishell(&args, &cmd, line, flag);
	}
	else
		error_exit("Too many arguments\n");
	rl_clear_history();
	return (args.exit_code);
}

/*
{
	readline 1

	Memcheck:Leak
	
	match-leak-kinds: reachable
	
	...

	obj:/usr/lib/aarch64-linux-gnu/libreadline.so.8.1
}

{
	readline 1

	Memcheck:Leak
	
	match-leak-kinds: reachable
	
	...

	obj:/usr/lib/x86_64-linux-gnu/libreadline.so.8.1
}*/
