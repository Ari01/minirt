/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:00:51 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 09:36:09 by user42           ###   ########.fr       */
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

t_rt	set_resolution(char **split, t_rt *rt)
{
	if (!split[1] || !split[2] || split[3])
		print_error_msg("invalid_resolution format");
	rt->width = ft_atoi(split[1]);
	rt->height = ft_atoi(split[2]);
	if (rt->width <= 0 || rt->height <= 0)
		print_error_msg("invalid resolution settings");
	return (rt);
}

t_rt	set_ambiant_light(char **split, t_rt *rt)
{
	char **tmp;

	if (!split[])
		return (rt);
	tmp = ft_split(split, ',');
	if (tmp[3])
		return (rt);
	rt->scene.ambiant_light.intensity = ft_atoi(split[1]);
	rt->scene.ambiant_light.color = new_color(ft_atoi(tmp[0]), ft_atoi(tmp))
}

t_rt	parse(char *pathfile)
{
	t_rt	rt;
	int		fd;
	char	**line;
	char	**split;

	fd = open(pathfile, O_RDONLY);
	line = NULL;
	rt = init_rt();
	while (get_next_line(fd, line) > 0)
	{
		split = ft_split(line, ' ');
		if (!ft_strnstr(ELEM_ID_SET, split[0], 1024))
			print_error_msg("unknown element id");
		if (!split || !*split || ft_strlen(split[0]) > 2)
			print_error_msg("")
		if (**line == 'R')
			rt = set_resolution(split, &rt);
		if (**line == 'A')
			rt = set_ambiant_light(split, &rt);
		if (**)
	}
	return (1);
}
