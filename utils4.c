/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divalent <divalent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:17:37 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 16:25:13 by divalent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_put_pid(void)
{
	char	*pid_res;
	int		fd;
	char	**stat;

	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
		return (close(fd), NULL);
	pid_res = ft_get_next_line(fd);
	close(fd);
	if (!pid_res)
		return (NULL);
	stat = ft_split(pid_res, ' ');
	free(pid_res);
	if (!stat)
		return (NULL);
	pid_res = ft_strdup(stat[0]);
	ft_free_array(stat);
	if (!pid_res)
		return (NULL);
	return (pid_res);
}

char	*ft_group_array(char **args, int i)
{
	char	*temp3;	
	char	*temp2;
	char	*temp;
	char	*new;

	new = NULL;
	if (!args && !args[i])
		return (NULL);
	if (args[i])
		new = ft_strdup(args[i]);
	i++;
	while (args[i] && args[i][0])
	{
		temp2 = ft_strdup(args[i++]);
		temp = ft_strjoin(" ", temp2);
		temp3 = ft_strjoin(new, temp);
		free(new);
		free(temp2);
		new = temp3;
		free(temp);
	}
	return (new);
}

t_args	*get_that_saved(t_args *args)
{
	static t_args	*saved;

	if (args)
		saved = args;
	return (saved);
}

void	good_close(t_command *cmd)
{
	if (cmd->input != 0 && cmd->input != 1)
		close(cmd->input);
	if (cmd->output != 1 && cmd->output != 0)
		close(cmd->output);
}

int	ft_good_if(char *line)
{
	return ((*(line + 1) == '_' || ft_isalnum(*(line + 1))
			|| *(line + 1) == DOLLAR || *(line + 1) == QUESTION));
}
