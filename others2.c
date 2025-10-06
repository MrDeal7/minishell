/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:39:13 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/29 19:39:25 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_sz(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**env_creator(void)
{
	char	**env;
	char	*pwd;
	char	*temp;

	env = malloc(sizeof(char *) * 5);
	pwd = getcwd(NULL, 0);
	env[0] = ft_strdup("PATH=/bin");
	temp = ft_strjoin("PWD=", pwd);
	env[1] = ft_strdup(temp);
	free(temp);
	temp = ft_strjoin("OLDPWD=", pwd);
	env[2] = ft_strdup(temp);
	free(temp);
	env[3] = ft_strdup("SHLVL=1");
	free(pwd);
	env[4] = NULL;
	return (env);
}

char	**init_envp(char **envp)
{
	char	**new;
	int		i;

	if (!*envp)
		return (env_creator());
	new = ft_calloc(ft_array_sz(envp) + 1, sizeof(char *));
	if (!new)
		error_exit("Error trying to alloc memory for env array\n");
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	envp[i] = NULL;
	return (new);
}
