/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:46:52 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/28 16:47:34 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_name_size(char *line)
{
	int	size;

	size = 0;
	while (line && line[size] != EQUAL)
		size++;
	return (size);
}

int	line_var_name_size(char *line)
{
	int	size;

	size = 0;
	while (line[size])
	{
		if (line[size] == '_' || ft_isalnum(line[size]))
			size++;
		else
			break ;
	}
	return (size);
}

int	longer_str(char *line_var, char *env)
{
	int	line_var_sz;
	int	env_sz;

	line_var_sz = line_var_name_size(line_var);
	env_sz = env_name_size(env);
	if (line_var_sz > env_sz)
		return (line_var_sz);
	else
		return (env_sz);
}

char	*env_search(t_args *args, char *line, int size)
{
	int		ii;
	char	*temp;

	ii = 0;
	if (*line == DOLLAR)
		line++;
	size = longer_str(line, args->env[ii]);
	while (args->env[ii] && ft_strncmp(line, args->env[ii], size) != 0)
	{
		ii++;
		size = longer_str(line, args->env[ii]);
	}
	temp = args->env[ii];
	if (!temp)
		return (NULL);
	if (args->env[ii][size] != EQUAL)
		return (NULL);
	while (*temp != EQUAL)
		temp++;
	temp++;
	return (temp);
}

int	dollar_expansion_size(t_args *args, char *line)
{
	int		i;
	char	*temp;
	int		var_name;

	i = 0;
	var_name = 0;
	if (line[i] == DOLLAR)
		i++;
	while (line[i])
	{
		if (line[i] == '_' || ft_isalnum(line[i]))
			i++;
		else
			break ;
	}
	temp = env_search(args, line, var_name);
	if (!temp)
		return (0);
	while (*temp)
	{
		var_name++;
		temp++;
	}
	return (var_name - i);
}
