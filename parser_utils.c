/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:40:05 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 19:40:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	string_array_free(char **split)
{
	int i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
		split = NULL;
	}
}

int		check_nargs(char **split, int nargs)
{
	int	i;

	i = 1;
	while (i <= nargs)
	{
		if (!split[i])
			return (0);
		i++;
	}
	return (1);
}

int		set_color(char **split, t_color *color)
{
	int valid_format;

	valid_format = 0;
	if (split && split[0] && split[1] && split[2] && !split[3])
	{
		*color = new_color(ft_atod(split[0]),
							ft_atod(split[1]),
							ft_atod(split[2]));
		if (color->r >= 0 && color->r <= 255
			&& color->g >= 0 && color->g <= 255
			&& color->b >= 0 && color->b <= 255)
			valid_format = 1;
	}
	string_array_free(split);
	return (valid_format);
}

int		set_coord(char **split, t_vector *coord)
{
	int	valid_format;

	valid_format = 1;
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		valid_format = 0;
	else
		*coord = new_vector(ft_atod(split[0]),
							ft_atod(split[1]),
							ft_atod(split[2]));
	if (isnan(coord->x) || isnan(coord->y) || isnan(coord->z))
		valid_format = 0;
	string_array_free(split);
	return (valid_format);
}

int		correct_direction(t_vector dir)
{
	if (dir.x < -1 || dir.x > 1
		|| dir.y < -1 || dir.y > 1
		|| dir.z < -1 || dir.z > 1)
		return (0);
	return (1);
}
