/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_focus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:37:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 18:37:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list	*grab_object_focus(t_rt *rt, t_list *objects)
{
	if (!objects || !objects->next)
		objects = rt->scene.objects;
	else
		objects = objects->next;
	rt->object = (t_object *)objects->content;
	rt->transform_focus = OBJECT;
	return (objects);
}

t_list	*grab_light_focus(t_rt *rt, t_list *lights)
{
	if (!lights || !lights->next)
		lights = rt->scene.light;
	else
		lights = lights->next;
	rt->light = (t_light *)lights->content;
	rt->transform_focus = LIGHT;
	return (lights);
}

void	grab_focus(int key, t_rt *rt, t_list **objects, t_list **lights)
{
	if (key == 'c')
		rt->transform_focus = CAMERA;
	if (key == 'o')
		*objects = grab_object_focus(rt, *objects);
	if (key == 'l')
		*lights = grab_light_focus(rt, *lights);
}
