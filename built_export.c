/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:20:39 by divalent          #+#    #+#             */
/*   Updated: 2024/10/31 21:16:44 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_print(t_args *args, int output)
{
	int	i;
	int	j;

	i = 0;
	while (args->exp[i] != NULL)
	{
		ft_putstr_fd("declare -x ", output);
		j = 0;
		while (args->exp[i][j])
		{
			if (args->exp[i][j] == '=' || args->exp[i][j] == '\0')
			{
				ft_putchar_fd(args->exp[i][j], output);
				ft_putchar_fd('"', output);
			}
			else
				ft_putchar_fd(args->exp[i][j], output);
			j++;
		}
		if (is_there_equal(args->exp[i]) == 1)
			ft_putchar_fd('"', output);
		ft_putchar_fd('\n', output);
		i++;
	}
}

int	ft_export_line_cout(t_args *args)
{
	int	i;
	int	nbr_lines;

	nbr_lines = 0;
	i = 0;
	while (args->env[i] != NULL)
	{
		if ((args->env[i][0] >= 'A' && args->env[i][0] <= 'Z') ||
				(args->env[i][0] >= 'a' && args->env[i][0] <= 'z'))
			nbr_lines++;
		i++;
	}
	return (nbr_lines);
}

void	ft_new_export_vars(t_args *args)
{
	int	nbr_lines;
	int	line_sz;
	int	i;
	int	j;

	nbr_lines = ft_export_line_cout(args);
	args->exp = ft_calloc((nbr_lines + 1), sizeof(char *));
	if (args->exp == NULL)
		error_exit("Error trying to alloc memory for exp array\n");
	i = 0;
	j = 0;
	while (i < nbr_lines)
	{
		if ((args->env[i][0] >= 'A' && args->env[i][0] <= 'Z') ||
				(args->env[i][0] >= 'a' && args->env[i][0] <= 'z'))
		{
			line_sz = (ft_strlen(args->env[i]) + 1);
			args->exp[j] = ft_calloc((line_sz), 1);
			ft_strlcpy(args->exp[j], args->env[i], line_sz);
			j++;
		}
		i++;
	}
	ft_sort(args->exp);
}

void	ft_export(t_args *args, t_command *cmd)
{
	int			i;

	i = 1;
	if (!cmd->args[1])
	{
		ft_export_print(args, cmd->output);
		return ;
	}
	while (cmd->args[i])
		args->env = add_line(args->env, cmd->args[i++], 0);
	i = 1;
	while (cmd->args[i])
	{
		if (ft_isvalid_export(cmd->args[i], 0))
			args->exp = add_line(args->exp, cmd->args[i], 1);
		else
		{
			error_print(" not a valid identifier");
			args->exit_code = 1;
			break ;
		}
		i++;
	}
}
