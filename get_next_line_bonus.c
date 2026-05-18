/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 07:01:11 by asobolev          #+#    #+#             */
/*   Updated: 2026/05/18 21:59:37 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*cleanup_error(char *buff, char **storage)
{
	free(buff);
	free(*storage);
	*storage = NULL;
	return (NULL);
}

static char	*return_remaining_storage(char *buff, char **storage)
{
	char	*tmp;

	free(buff);
	if (*storage)
	{
		tmp = *storage;
		*storage = NULL;
		return (tmp);
	}
	return (NULL);
}

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
	*storage = ft_substr(tmp, len, ft_strlen(tmp));
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			readed;
	static char	*storage[1048576];

	if ((fd < 0) || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (1)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (cleanup_error(buff, &storage[fd]));
		if (readed == 0)
			return (return_remaining_storage(buff, &storage[fd]));
		buff[readed] = '\0';
		append_buffer(&storage[fd], buff);
		if (storage[fd] && ft_strchr(storage[fd], '\n'))
			return (extract_line(&storage[fd]));
	}
	return (NULL);
}
