/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:48:52 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 18:18:28 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_split(char const *str, char c)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			cnt++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (cnt);
}

static char	*input_split_row(char const *str, char c)
{
	char	*res;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, len + 1);
	return (res);
}

static char	**input_split(char **split, size_t count, char const *str, char c)
{
	size_t	row;

	row = 0;
	while (row < count)
	{
		while (*str == c)
			str++;
		if (*str)
		{
			split[row] = input_split_row(str, c);
			if (!split[row])
			{
				while (row > 0)
					free(split[--row]);
				free(split);
				return (NULL);
			}
		}
		while (*str && *str != c)
			str++;
		row++;
	}
	split[row] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_split(s, c);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	return (input_split(split, count, s, c));
}
