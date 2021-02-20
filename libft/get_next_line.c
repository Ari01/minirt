/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:34:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/11 11:58:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		read_line(int fd, char **linebuf)
{
	char	buf[BUFFER_SIZE + 1];
	char	*freeptr;
	int		read_value;

	read_value = read(fd, buf, BUFFER_SIZE);
	while (read_value > 0)
	{
		buf[read_value] = 0;
		freeptr = *linebuf;
		*linebuf = ft_strjoin(*linebuf, buf);
		if (!*linebuf)
			return (-1);
		free(freeptr);
		freeptr = NULL;
		if (ft_strchr(*linebuf, '\n'))
			return (1);
		read_value = read(fd, buf, BUFFER_SIZE);
	}
	return (read_value);
}

char	*trim_line(char **linebuf)
{
	char	*freeptr;
	char	*line;
	char	*endline;
	size_t	len;

	freeptr = *linebuf;
	endline = ft_strchr(*linebuf, '\n');
	if (endline)
		len = endline - *linebuf;
	else
		len = ft_strlen(*linebuf);
	line = ft_substr(*linebuf, 0, len);
	if (!line)
		return (NULL);
	len++;
	*linebuf = ft_substr(*linebuf, len, ft_strlen(*linebuf) - len);
	if (!linebuf)
	{
		free(line);
		line = NULL;
	}
	free(freeptr);
	freeptr = NULL;
	return (line);
}

int		get_next_line(int fd, char **line)
{
	static char	*linebuf;
	int			read_value;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	if (!linebuf)
		linebuf = ft_strdup("");
	if (!linebuf)
		return (-1);
	read_value = read_line(fd, &linebuf);
	if (read_value < 0)
		return (-1);
	if (ft_strchr(linebuf, '\n'))
		read_value = 1;
	*line = trim_line(&linebuf);
	if (!line || !read_value)
	{
		free(linebuf);
		linebuf = NULL;
		if (!line)
			return (-1);
	}
	return (read_value);
}
