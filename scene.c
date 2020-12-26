/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:17:48 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 08:27:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene	init_scene()
{
	t_scene s;

	s.ambiant_light = init_ambiant_light();
	s.light = NULL;
	s.camera = NULL;
	s.objects = NULL;
	return (s);
}
