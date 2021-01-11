/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 17:08:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		exit_prog(t_rt *rt)
{
	free_rt(rt);
	exit(EXIT_SUCCESS);
}

int		key_hook(int key, t_rt *rt)
{
	if (key == ESCAPE)
		exit_prog(rt);
	if (key == TAB)
		rt->transform_focus = (rt->transform_focus + 1 == 2 ? 0 : 1);
	if (key == 't')
		rt->transform = (rt->transform + 1 == 2 ? 0 : 1);
	if (key == 'q' || key == 'd' || key == 'z' || key == 's' || key == CONTROL || key == SPACE)
	{
		if (rt->transform_focus == CAMERA)
			rt->transform == TRANSLATE ? move_camera(key, rt) : rotate_camera(key, rt);
	/*	else
		{
			rt->transform == TRANSLATE ? move_objec(key, rt) : rotate_object(key, rt);	
		}*/
		render(rt);
	}
	return (0);
}
