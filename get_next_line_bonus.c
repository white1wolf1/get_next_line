/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 07:01:11 by asobolev          #+#    #+#             */
/*   Updated: 2026/05/19 01:34:59 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*append_buffer(char **storage, char *buff)
{
	char	*tmp;

	if (!*storage)
	{
		*storage = ft_strdup(buff);
		return (*storage);
	}
	tmp = ft_strjoin(*storage, buff);
	free(*storage);
	*storage = tmp;
	return (*storage);
}

static char	*extract_line(char **storage)
{
	char	*tmp;
	char	*line;
	char	*newline;
	int		len;

	tmp = *storage;
	newline = ft_strchr(tmp, '\n');
	if (newline)
		len = (newline - tmp) + 1;
	else
		len = ft_strlen(tmp);
	line = ft_substr(tmp, 0, len);
	if (len >= (int)ft_strlen(tmp))
		*storage = NULL;
	else
		*storage = ft_substr(tmp, len, ft_strlen(tmp) - len);
	free(tmp);
	return (line);
}

static char	*handle_read_result(int readed, char *buff, char **storage)
{
	char	*tmp;

	if (readed == -1)
	{
		free(buff);
		free(*storage);
		*storage = NULL;
		return (NULL);
	}
	free(buff);
	if (*storage)
	{
		tmp = *storage;
		*storage = NULL;
		return (tmp);
	}
	return (NULL);
}

static char	*read_until_line(int fd, char *buff, char **storage)
{
	int	readed;

	while (1)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed <= 0)
			return (handle_read_result(readed, buff, storage));
		buff[readed] = '\0';
		*storage = append_buffer(storage, buff);
		if (!*storage)
		{
			free(buff);
			return (NULL);
		}
		if (ft_strchr(*storage, '\n'))
		{
			free(buff);
			return (extract_line(storage));
		}
	}
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*storage[1048576];

	if ((fd < 0) || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	return (read_until_line(fd, buff, &storage[fd]));
}
