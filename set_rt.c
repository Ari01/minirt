/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 18:21:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_missing_parameters(t_rt *rt)
{
	if (rt->width <= 0 || rt->height <= 0)
		print_error_msg("missing resolution");
	if (rt->scene.ambiant_light.intensity <= 0)
		print_error_msg("missing ambiant light");
	if (!rt->scene.camera)
		print_error_msg("missing camera");
	if (!rt->scene.objects)
		print_error_msg("missing object");
}

t_rt	set_rt(char *pathfile)
{
	t_rt		rt;
	int			fd;
	int			valid_file;
	char		*line;
	char		*linebuf;

	linebuf = NULL;
	line = NULL;
	valid_file = 1;
	rt = init_rt();
	if ((fd = open(pathfile, O_RDONLY)) == -1)
		ft_perror();
	while (get_next_line(fd, &line, &linebuf) > 0)
	{
		if (*line)
			valid_file = set_scene(line, &rt);
		free(line);
		if (!valid_file)
		{
			free(linebuf);
			parsing_error(&rt, "invalid rt file");
		}
	}
	free(line);
	check_missing_parameters(&rt);
	return (rt);
}
