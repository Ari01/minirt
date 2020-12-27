/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 07:21:00 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 11:47:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

double	ft_atod(char *s)
{
	double	atod;
	double	tmp;

	atod = ft_atoi(s);
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
		s++;
	if (*s && !ft_isdigit(*s))
	{
		ft_putendl_fd("invalid double number", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	tmp = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s)
	{
		ft_putendl_fd("invalid double number", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (tmp >= 1)
		tmp = tmp / 10;
	return (atod + tmp);
}
