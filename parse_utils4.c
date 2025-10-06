/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:09:03 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:13:17 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_sz(char *str, int i)
{
	char	*temp;

	temp = str;
	while (*temp)
	{
		if (*temp == D_QUOTE)
		{
			i += ((ft_sz_in_quotes(temp, D_QUOTE) + 1) + 1);
			temp = ft_ignore_while_not(temp, D_QUOTE) + 1;
		}
		else if (*temp == QUOTE)
		{
			i += ((ft_sz_in_quotes(temp, QUOTE) + 1) + 1);
			temp = ft_ignore_while_not(temp, QUOTE) + 1;
		}
		else if (*temp == SPACES || *temp == TABS)
			break ;
		else
		{
			i++;
			temp++;
		}
	}
	return (i);
}

char	*ft_split_skip(char *str)
{
	char	*temp;

	temp = str;
	while (*temp)
	{
		if (*temp == D_QUOTE)
			temp = ft_ignore_while_not(temp, D_QUOTE) + 1;
		else if (*temp == QUOTE)
			temp = ft_ignore_while_not(temp, QUOTE) + 1;
		else if (*temp == SPACES || *temp == TABS)
		{
			temp = ft_skip_spaces(temp);
			break ;
		}
		else
			temp++;
	}
	return (temp);
}

void	strings_content2(char **split, char *str, int quotes_on)
{
	int	sub_str_sz;
	int	sub_str_index;

	sub_str_index = 0;
	while (*str)
	{
		sub_str_sz = ft_str_sz(str, 0);
		split[sub_str_index] = ft_calloc(sub_str_sz + 3, sizeof(char));
		if (quotes_on)
			ft_strlcpy_w_quotes(split, str, &sub_str_index, sub_str_sz);
		else
			ft_special_strlcpy(split, str, &sub_str_index, sub_str_sz);
		str = ft_split_skip(str);
		sub_str_index++;
	}
}

char	**ft_split_args(char *str, int quotes_on)
{
	int		sub_string_count;
	char	**split;
	char	*s_copy;

	s_copy = str;
	split = NULL;
	while (*s_copy == SPACES || *s_copy == TABS)
		s_copy++;
	sub_string_count = string_counter(s_copy);
	if (!str[0])
		return (NULL);
	split = ft_calloc(sub_string_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	strings_content2(split, s_copy, quotes_on);
	return (split);
}

void	ft_expansions(t_args *args)
{
	t_command	*temp;

	temp = args->cmd;
	while (temp)
	{
		temp->line = ft_expand_vars(args, temp->line);
		temp->args = ft_split_args(temp->line, 0);
		temp->redir = ft_redir_args(temp, ft_count_apends(temp->line, 0) \
			+ ft_count_redirects(temp->line, 0));
		temp = temp->next;
	}
	temp = args->cmd;
	while (temp)
	{
		free(temp->line);
		temp->line = ft_group_array(temp->args, 0);
		temp = temp->next;
	}
}
