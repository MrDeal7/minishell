/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:11:43 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:13:18 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_rdir_helper(char **str, int k)
{
	int	j;

	j = k;
	free(str[k]);
	str[k] = NULL;
	k++;
	free(str[k]);
	str[k] = NULL;
	k++;
	while (str[k])
	{
		str[j++] = ft_strdup(str[k]);
		free(str[k]);
		str[k] = NULL;
		k++;
	}
}

void	ft_delete_rdir(t_command *cmd)
{
	char	**temp;
	int		i;
	int		k;
	int		count;

	i = 0;
	count = 0;
	if (!cmd)
		return ;
	temp = ft_dup_arr(cmd->args);
	while (temp[i])
	{
		k = i;
		if (*temp[k] == RD_IN || *temp[k] == RD_OUT)
			ft_delete_rdir_helper(temp, k);
		else
			i++;
		count++;
	}
	i = -1;
	ft_free_array(cmd->args);
	cmd->args = ft_calloc(count + 1, sizeof(char *));
	while (temp[++i])
		cmd->args[i] = temp[i];
	free(temp);
}

void	ft_redir_args_helper(t_command *cmd, bool *rdir_flag, char **temp, \
			char *temp2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i] && cmd->args[i + 1] && cmd->args[i][0] == RD_IN \
			&& cmd->args[i + 1][0])
		{
			temp2 = ft_strjoin(cmd->args[i], " ");
			temp[j++] = ft_strjoin(temp2, cmd->args[i + 1]);
			free(temp2);
			*rdir_flag = true;
		}
		else if (cmd->args[i] && cmd->args[i + 1] && cmd->args[i][0] == RD_OUT \
			&& cmd->args[i + 1][0])
		{
			temp2 = ft_strjoin(cmd->args[i], " ");
			temp[j++] = ft_strjoin(temp2, cmd->args[i + 1]);
			free(temp2);
			*rdir_flag = true;
		}
		i++;
	}
}

char	**ft_redir_args(t_command *cmd, int size)
{
	char	**temp;
	bool	rdir_flag;

	temp = NULL;
	if (!cmd->args)
		return (NULL);
	rdir_flag = false;
	if (size != 0)
		temp = ft_calloc(size + 1, sizeof(char *));
	else
		return (NULL);
	if (!temp)
		return (NULL);
	ft_redir_args_helper(cmd, &rdir_flag, temp, NULL);
	if (rdir_flag == true)
		ft_delete_rdir(cmd);
	return (temp);
}
