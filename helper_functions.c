/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:56:08 by divalent          #+#    #+#             */
/*   Updated: 2024/10/29 16:05:53 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_e(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] != '=')
		i++;
	return (i);
}

bool	is_there_line(char **env, char *line)
{
	int	i;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], line, len_e(line)) != 0
			|| len_e(line) != len_e(env[i])))
		i++;
	if (ft_strncmp(env[i], line, len_e(env[i])) == 0
		&& len_e(line) == len_e(env[i]))
		return (true);
	else
		return (false);
}

int	is_there_equal(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] != '=')
		i++;
	if (line[i] && line[i] == '=')
		return (1);
	return (0);
}

char	**remove_from_line(char **env, char *line)
{
	char	**env_return;
	int		i;
	int		k;

	env_return = NULL;
	i = 0;
	if (is_there_line(env, line) == false)
		return (env);
	while (env[i])
		i++;
	env_return = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (env[i] && (ft_strncmp(env[i], line, len_e(line)) != 0
			|| len_e(line) != len_e(env[i])))
	{
		env_return[i] = env[i];
		i++;
	}
	k = i;
	free(env[i++]);
	while (env[i])
		env_return[k++] = env[i++];
	free(env);
	env_return[k] = NULL;
	return (env_return);
}

char	**add_line(char **env, char *line, int exp)
{
	char	**env_return;
	int		i;
	int		k;

	i = 0;
	if (exp == 0 && is_there_equal(line) == 0)
		return (env);
	while (env[i] && (ft_strncmp(env[i], line, len_e(line)) != 0
			|| len_e(line) != len_e(env[i])))
		i++;
	k = i;
	while (env[k])
		k++;
	env_return = (char **)malloc(sizeof(char *) * (k + 2));
	k = -1;
	while (env[++k] && k < i)
		env_return[k] = env[k];
	if (env[i])
		free(env[i]);
	env_return[k++] = ft_strdup(line);
	while (env[i])
		env_return[k++] = env[++i];
	env_return[k] = NULL;
	free(env);
	return (env_return);
}
