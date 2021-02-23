/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 09:15:33 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 18:29:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_perror(void)
{
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}

void	print_error_msg(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	parsing_error(t_rt *rt, char *msg)
{
	free_rt(rt);
	print_error_msg(msg);
}
