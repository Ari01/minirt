/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:14:46 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 08:26:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rt	init_rt()
{
	t_rt rt;

	rt.width = -1;
	rt.height = -1;
	rt.scene = init_scene();
	return (rt);
}
