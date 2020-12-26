/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:15:21 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 09:31:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "get_next_line.h"
# include "types.h"
# include <fcntl.h>
# include <stdlib.h>

# define ELEM_ID_SET "R,A,c,l,sp,pl,sq,cy,tr"

t_rt	init_rt();
t_scene init_scene();
t_light	init_ambiant_light();
t_color	new_color(double r, double g, double b);

void	print_error_msg(char *msg);

#endif
