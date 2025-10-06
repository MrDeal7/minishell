/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:14:58 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:13:18 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore(struct sigaction *si_ha, int signal)
{
	struct sigaction	orig;
	int					orig_flags;

	orig_flags = si_ha->sa_flags;
	si_ha->sa_handler = SIG_IGN;
	si_ha->sa_flags |= SA_SIGINFO;
	sigemptyset(&si_ha->sa_mask);
	sigaction(signal, si_ha, &orig);
	si_ha->sa_flags = orig_flags;
}

void	ft_heredoc(int signal, siginfo_t *si_ha, void *unused)
{
	t_args	*args;

	args = get_that_saved(NULL);
	(void) unused;
	(void) si_ha;
	if (signal == SIGINT)
		ft_putchar_fd('\n', 1);
	ft_exitcode(130);
	free(args->cmd->temp);
	free_children(args, args->cmd);
	close_all_fds();
	exit (130);
}

void	signal_handler2(t_type sig, struct sigaction si_ha)
{
	if (sig == HERE_DOC)
	{
		si_ha.sa_sigaction = ft_heredoc;
		si_ha.sa_flags = SA_SIGINFO;
		sigemptyset(&si_ha.sa_mask);
		sigaction(SIGINT, &si_ha, NULL);
		ignore(&si_ha, SIGQUIT);
	}
	else if (sig == IGNORE)
	{
		ignore(&si_ha, SIGINT);
		ignore(&si_ha, SIGQUIT);
	}
	else if (sig == CLOSE_PIPE)
	{
		si_ha.sa_sigaction = ft_closepipe;
		si_ha.sa_flags = SA_SIGINFO;
		sigemptyset(&si_ha.sa_mask);
		sigaction(SIGPIPE, &si_ha, NULL);
		ignore(&si_ha, SIGPIPE);
	}
}

void	signal_handler(t_type sig)
{
	static struct sigaction	si_ha;

	if (sig == PARENT)
	{
		si_ha.sa_sigaction = ft_sig_int;
		si_ha.sa_flags = SA_SIGINFO;
		sigemptyset(&si_ha.sa_mask);
		sigaction(SIGINT, &si_ha, NULL);
		ignore(&si_ha, SIGQUIT);
	}
	else if (sig == CHILD)
	{
		si_ha.sa_sigaction = ft_child;
		si_ha.sa_flags = 0;
		sigemptyset(&si_ha.sa_mask);
		sigaction(SIGINT, &si_ha, NULL);
		sigaction(SIGQUIT, &si_ha, NULL);
	}
	else
		signal_handler2(sig, si_ha);
}
