/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 07:21:00 by user42            #+#    #+#             */
/*   Updated: 2021/01/01 14:06:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void		print_error_msg()
{
	ft_putendl_fd("invalid double number", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

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
		print_error_msg();
	while (tmp >= 1)
		tmp = tmp / 10;
	return ((atod + tmp) * minus);
}
