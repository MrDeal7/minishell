/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:37:48 by divalent          #+#    #+#             */
/*   Updated: 2024/11/01 20:40:45 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_caller(t_args *args, t_command *cmd, t_code built_in)
{
	if (built_in == OTHER)
		execution(cmd, args->env, args);
	else
		built_in_execution(args, cmd, built_in);
}

int	spaces_handler(char **line)
{
	while (**line && (**line == SPACES || **line == TABS))
		(*line)++;
	if (**line == '\0')
		return (1);
	return (0);
}

void	free_children(t_args *args, t_command *cmd)
{
	if (cmd)
		ft_clear_cmd_list(&cmd);
	if (args)
	{
		if (args->env)
			ft_free_array(args->env);
		if (args->exp)
			ft_free_array(args->exp);
	}
}
