/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 09:15:33 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:41:36 by user42           ###   ########.fr       */
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

int		is_elem_id(char *id)
{
	if (!ft_strnstr(ELEM_ID_SET, id, 1024))
		return (0);
	return (1);
}
