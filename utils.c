/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:04:31 by adimas-d          #+#    #+#             */
/*   Updated: 2024/10/31 21:16:48 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *error)
{
	ft_printf(RED"%s"RST, error);
	exit(EXIT_FAILURE);
}

void	error_print(char *error)
{
	ft_putendl_fd(error, 2);
}

void	ft_sort(char **sort)
{
	int		i;
	int		j;
	int		line_sz;
	char	*tmp;

	i = 0;
	while (sort[i + 1])
	{
		j = i + 1;
		while (sort[j])
		{
			line_sz = strlen(sort[i]);
			if (ft_strncmp(sort[i], sort[j], line_sz) > 0)
			{
				tmp = sort[i];
				sort[i] = sort[j];
				sort[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

int	ft_cd_erro(int cd)
{
	if (cd == 0)
		return (0);
	if (cd == ENOENT)
		ft_putendl_fd(" No such file or directory", 2);
	else if (cd == EACCES)
		ft_putendl_fd(" Search permission was denied on the directory\
			 open on fd", 2);
	else if (cd == EBADF)
		ft_putendl_fd(" fd is not a valid file descriptor", 2);
	else if (cd == ENOTDIR)
		ft_putendl_fd(" fd does not refer to a directory", 2);
	else if (cd == ENAMETOOLONG)
		ft_putendl_fd(" path is too long", 2);
	else if (cd == 3000)
		ft_putendl_fd(" too many arguments", 2);
	return (1);
}
