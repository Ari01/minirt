/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 14:52:15 by user42           ###   ########.fr       */
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

void	set_rt(char *line, t_rt *rt)
{
	char **split;

	split = ft_split(line, " \t");
	if (!split || !*split)
		print_error_msg("couldn't read line");
	if (!ft_strnstr(ELEM_ID_SET, split[0], 1024))
		print_error_msg("invalid element id");
	if (!ft_strncmp(split[0], "R", 2))
		set_resolution(split, rt);
	if (!ft_strncmp(split[0], "A", 2))
		set_ambiant_light(split, rt);
	if (!ft_strncmp(split[0], "c", 2))
		set_camera(split, rt);
	if (!ft_strncmp(split[0], "l", 2))
		set_light(split, rt);
	if (!ft_strncmp(split[0], "sp", 2))
		set_sphere(split, rt);
	if (!ft_strncmp(split[0], "pl", 2))
		set_plane(split, rt);
	if (!ft_strncmp(split[0], "sq", 2))
		set_square(split, rt);
	if (!ft_strncmp(split[0], "cy", 2))
		set_cylindre(split, rt);
	if (!ft_strncmp(split[0], "tr", 2))
		set_triangle(split, rt);
	string_array_free(split);
}

t_rt	parse(char *pathfile)
{
	t_rt	rt;
	int		fd;
	char	*line;

	rt = init_rt();
	line = NULL;
	fd = open(pathfile, O_RDONLY);
	if (fd == -1)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
		{
			set_rt(line, &rt);
			free(line);
			line = NULL;
		}
	}
	check_missing_parameters(&rt);
	return (rt);
}
