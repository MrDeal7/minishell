/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:47:18 by adimas-d          #+#    #+#             */
/*   Updated: 2023/12/04 21:29:59 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_buffer_clear(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		buffer[i++] = '\0';
}

static int	ft_get_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*ft_get_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_get_strlen(s1) + ft_get_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		if (s2[j] == '\n')
			break ;
		j++;
	}
	free (s1);
	new[i] = '\0';
	return (new);
}

static int	ft_newline_check(char *buffer)
{
	int	has_new_line;
	int	i;
	int	j;

	has_new_line = 0;
	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (has_new_line)
		{
			buffer[j] = buffer[i];
			j++;
		}
		if (buffer[i] == '\n')
			has_new_line = 1;
		buffer[i] = 0;
		i++;
	}
	return (has_new_line);
}

char	*ft_get_next_line(int fd)
{
	char		*line_to_write;
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];

	line_to_write = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0 && fd <= FOPEN_MAX)
			ft_buffer_clear(buffer[fd]);
		return (NULL);
	}
	while (*buffer[fd] != 0 || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		line_to_write = ft_get_strjoin(line_to_write, buffer[fd]);
		if (ft_newline_check(buffer[fd]))
			break ;
	}
	return (line_to_write);
}
