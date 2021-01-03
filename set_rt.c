/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 14:01:15 by user42           ###   ########.fr       */
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
	t_rt	rt;
	int		fd;
	int		valid_file;
	char	*line;
	char	**split;

	rt = init_rt();
	line = NULL;
	split = NULL;
	fd = open(pathfile, O_RDONLY);
	valid_file = 1;
	if (fd == -1)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			valid_file = set_scene(line, split, &rt);
		free(line);
		line = NULL;
		if (!valid_file)
			print_error_msg("invalid rt file");
	}
	free(line);
	check_missing_parameters(&rt);
	return (rt);
}
