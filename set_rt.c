/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 20:27:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_missing_parameters(t_rt *rt)
{
	if (rt->width <= 0 || rt->height <= 0)
		parsing_error(rt, "missing resolution");
	if (rt->scene.ambiant_light.intensity <= 0)
		parsing_error(rt, "missing ambiant light");
	if (!rt->scene.camera)
		parsing_error(rt, "missing camera");
	if (!rt->scene.objects)
		parsing_error(rt, "missing object");
}

void	read_file(t_rt *rt, int fd)
{
	char	*line;
	char	*linebuf;
	int		valid_file;

	linebuf = NULL;
	line = NULL;
	valid_file = 1;
	while (get_next_line(fd, &line, &linebuf) > 0)
	{
		if (*line)
			valid_file = set_scene(line, rt);
		free(line);
		if (!valid_file)
		{
			free(linebuf);
			parsing_error(rt, "invalid rt file");
		}
	}
	free(line);
}

t_rt	set_rt(char *pathfile)
{
	t_rt		rt;
	int			fd;

	rt = init_rt();
	if ((fd = open(pathfile, O_RDONLY)) == -1)
		ft_perror();
	read_file(&rt, fd);
	check_missing_parameters(&rt);
	return (rt);
}
