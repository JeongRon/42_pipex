/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:54:32 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/17 15:36:55 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static int	check_buff(char *buff)
{
	int	i;

	if (!buff)
		return (1);
	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static char	*make_buff(char *buff, int fd, int read_size)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	tmp[BUFFER_SIZE] = '\0';
	while (check_buff(buff) == 1)
	{
		read_size = read(fd, tmp, BUFFER_SIZE);
		if (read_size == -1)
		{
			free_all(buff, tmp);
			return (NULL);
		}
		else if (read_size == 0)
			break ;
		buff = ft_strjoin(buff, tmp, read_size);
		if (!buff)
		{
			free_all(buff, tmp);
			return (NULL);
		}
	}
	free(tmp);
	return (buff);
}

static char	*make_line(char *buff, int line_len)
{
	char	*new_line;
	int		i;

	if (line_len == -1)
	{
		new_line = ft_strdup(buff);
		if (!new_line)
			return (NULL);
	}
	else
	{
		new_line = (char *)malloc(sizeof(char) * (line_len + 1));
		if (!new_line)
			return (NULL);
		i = 0;
		while (i < line_len)
		{
			new_line[i] = buff[i];
			i++;
		}
		new_line[i] = '\0';
	}
	return (new_line);
}

static char	*make_cache(char *buff, char *line, int line_len)
{
	char	*new_cache;
	int		buff_len;
	int		i;
	int		j;

	buff_len = ft_strlen(buff);
	if (line_len == -1 || buff_len == line_len)
		return (NULL);
	new_cache = (char *)malloc(sizeof(char) * (buff_len - line_len + 1));
	if (!new_cache)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	i = 0;
	j = line_len;
	while (j < buff_len)
	{
		new_cache[i] = buff[j];
		i++;
		j++;
	}
	new_cache[i] = '\0';
	return (new_cache);
}

char	*get_next_line(int fd)
{
	static char	*cache[_OPEN_MAX];
	char		*buff;
	char		*line;
	int			line_len;

	if (fd < 0 || fd > _OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (cache[fd])
	{
		buff = ft_strdup(cache[fd]);
		if (!buff)
			return (NULL);
		free(cache[fd]);
		cache[fd] = NULL;
	}
	else
		buff = NULL;
	buff = make_buff(buff, fd, 0);
	if (!buff)
		return (NULL);
	line_len = ft_linelen(buff);
	line = make_line(buff, line_len);
	cache[fd] = make_cache(buff, line, line_len);
	free(buff);
	return (line);
}
