/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:19:24 by divalent          #+#    #+#             */
/*   Updated: 2024/10/31 13:12:29 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd_error(int pwd)
{
	if (pwd == EACCES)
		error_print("Permission to read or search a component of the \
			filename was denied.");
	else if (pwd == EFAULT)
		error_print("buf points to a bad address.");
	else if (pwd == EINVAL)
		error_print("The size argument is zero and buf is not a null pointer.");
	else if (pwd == ENAMETOOLONG)
		error_print("The size of the null-terminated absolute pathname string \
			exceeds PATH_MAX bytes.");
	else if (pwd == ENOENT)
		error_print("The current working directory has been unlinked.");
	else if (pwd == ENOMEM)
		error_print("Out of memory.");
	else if (pwd == ERANGE)
		error_print("The size argument is less than the length of the absolute \
			pathname of the working directory, including the terminating null byte. \
			You need to allocate a bigger array and try again.");
}

void	ft_update_oldpwd(t_args *args)
{
	int		i;
	char	*old_pwd;
	char	*old_pwd_dir;

	i = 0;
	old_pwd = "OLDPWD=";
	old_pwd_dir = getcwd(NULL, 0);
	while (args->env[i] && ft_strncmp(args->env[i], "OLDPWD=", 5) != 0)
		i++;
	if (!args->env[i])
		args->env = ft_add_to_array(args->env,
				ft_strjoin(old_pwd, old_pwd_dir));
	else
	{
		free (args->env[i]);
		args->env[i] = ft_strjoin(old_pwd, old_pwd_dir);
	}
	free (old_pwd_dir);
}

void	ft_update_pwd(t_args *args)
{
	char	*new_pwd;
	int		i;

	new_pwd = getcwd(NULL, 0);
	i = 0;
	while (args->env[i] && ft_strncmp(args->env[i], "PWD=", 4) != 0)
		i++;
	free(args->env[i]);
	args->env[i] = ft_strjoin("PWD=", new_pwd);
	if (!args->env[i])
		error_print("Error updating env PWD.");
	free(new_pwd);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		ft_pwd_error(errno);
	else
		ft_printf("%s\n", pwd);
	free(pwd);
	return (1);
}
