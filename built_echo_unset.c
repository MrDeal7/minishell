/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:03:42 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:33:35 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_opt(char **args)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	if (!args || !args[i])
		return (0);
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			if (!args[i][j] && args[i][j] != 'n')
				return (i);
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (args[i][j])
				return (i);
			j = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	ft_echo(char **args, int output)
{
	int		opt;
	char	*new;

	new = NULL;
	if (args[0] && !args[1])
		return ;
	opt = check_echo_opt(args);
	if (opt > 1)
	{
		if (args[opt])
			new = ft_group_array(args, opt);
		ft_putstr_fd(new, output);
	}
	else
	{
		new = ft_group_array(args, 1);
		ft_putendl_fd(new, output);
	}
	free(new);
}

void	ft_unset(t_args *args, t_command *cmd)
{
	char	**lines;
	int		i;

	i = 1;
	if (!args->env)
		return ;
	lines = ft_split(cmd->line, ' ');
	while (lines[i])
		args->env = remove_from_line(args->env, lines[i++]);
	i = 1;
	while (lines[i])
		args->exp = remove_from_line(args->exp, lines[i++]);
	ft_free_array(lines);
}
