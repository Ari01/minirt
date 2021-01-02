/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/02 16:10:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_scene(char *line, char **split, t_rt *rt)
{
	int		valid_scene;

	valid_scene = 1;
	split = ft_split(line, " \t");
	(void)rt;
	if (!split || !*split || !ft_strnstr(ELEM_ID_SET, split[0], 1024))
		valid_scene = 0;
	else if (!ft_strncmp(split[0], "R", 2))
		valid_scene = set_resolution(split, rt);
	else if (!ft_strncmp(split[0], "A", 2))
		valid_scene = set_ambiant_light(split, rt);
	else if (!ft_strncmp(split[0], "c", 2))
		valid_scene = set_camera(split, rt);
	else if (!ft_strncmp(split[0], "l", 2))
		valid_scene = set_light(split, rt);
	else if (!ft_strncmp(split[0], "sp", 2))
		valid_scene = set_sphere(split, rt);
	else if (!ft_strncmp(split[0], "pl", 2))
		valid_scene = set_plane(split, rt);
	else if (!ft_strncmp(split[0], "sq", 2))
		valid_scene = set_square(split, rt);
	else if (!ft_strncmp(split[0], "cy", 2))
		valid_scene = set_cylindre(split, rt);
	else if (!ft_strncmp(split[0], "tr", 2))
		valid_scene = set_triangle(split, rt);
	string_array_free(split);
	return (valid_scene);
}

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
//	int		valid_file;
	char	*line;
	char	**split;

	rt = init_rt();
	line = NULL;
	split = NULL;
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
			//valid_file = set_scene(line, split, &rt);
			free(line);
			line = NULL;
		//	if (!valid_file)
		//		print_error_msg("invalid rt file");
		}
	}
	free(line);
	//check_missing_parameters(&rt);
	return (rt);
}
