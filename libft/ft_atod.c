/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 07:21:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 19:36:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

double			ft_atod(char *s)
{
	double	atod;
	double	tmp;
	int		minus;

	minus = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			minus *= -1;
		s++;
	}
	atod = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
		s++;
	tmp = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s)
		return (NAN);
	while (tmp >= 1)
		tmp = tmp / 10;
	return ((atod + tmp) * minus);
}
