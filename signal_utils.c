/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:46:39 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/29 20:06:34 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closepipe(int signal, siginfo_t *si_ha, void *unused)
{
	(void)unused;
	(void)si_ha;
	if (signal == SIGPIPE)
		ft_exitcode(127);
}

void	ft_child(int signal, siginfo_t *si_ha, void *unused)
{
	(void)unused;
	(void)si_ha;
	if (signal == SIGINT)
		ft_exitcode(130);
	if (signal == SIGQUIT)
		ft_exitcode(131);
}

void	ft_sig_int(int signal, siginfo_t *si_ha, void *unused)
{
	(void)unused;
	(void)si_ha;
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	ft_exitcode(130);
}

t_exit	ft_start_exitcode(t_args *args)
{
	static t_exit	exit_code;

	if (args)
		exit_code.args = args;
	return (exit_code);
}

void	ft_exitcode(int code)
{
	t_exit	temp;

	temp = ft_start_exitcode(NULL);
	temp.args->exit_code = code;
}
