/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 10:33:41 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 12:07:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int		read_from_line(int fd, char **linebuf)
{
	int		read_value;
	char	buff[BUFFER_SIZE];
	char	*tmp;

	read_value = 1;
	if (BUFFER_SIZE <= 0)
		return (-1);
	while ((read_value = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_value] = 0;
		if (!*linebuf)
			*linebuf = ft_strdup(buff);
		else
		{
			tmp = *linebuf;
			*linebuf = ft_strjoin(*linebuf, buff);
			free(tmp);
		}
		if (ft_strchr(*linebuf, '\n'))
			return (1);
	}
	return (read_value);
}

int		read_from_linebuf(char **linebuf, char **line)
{
	char	*endline;
	char	*tmp;
	size_t	len;

	if (!*linebuf)
		return (-1);
	endline = ft_strchr(*linebuf, '\n');
	len = 0;
	if (endline)
	{
		len = endline - *linebuf;
		*line = ft_substr(*linebuf, 0, len);
		tmp = *linebuf;
		*linebuf = ft_strdup(*linebuf + len + 1);
		if (!*line || !*linebuf)
			return (-1);
		free(tmp);
		return (1);
	}
	*line = ft_strdup(*linebuf);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*linebuf;
	int				read_line;
	int				read_buf;

	read_line = 1;
	if (!linebuf || !*linebuf)
		read_line = read_from_line(fd, &linebuf);
	read_buf = read_from_linebuf(&linebuf, line);
	if (read_line == -1 || read_buf == -1)
	{
		free(linebuf);
		return (-1);
	}
	if (!read_buf)
	{
		free(linebuf);
		return (0);
	}
	return (1);
}
