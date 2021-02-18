/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 12:01:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int ac, char **av)
{
	t_rt rt;
	
	if (ac == 2 || (ac == 3 && !ft_strncmp(av[2], "-save", ft_strlen(av[2]))))
	{
		rt = set_rt(av[1]);
		set_mlx(&rt);
		render(&rt);
		if (ac == 3)
			img_to_bmp(&rt, "test.bmp");
		mlx_hook(rt.window, 33, 1L<<0, &exit_prog, &rt);
		mlx_hook(rt.window, 12, 1L<<15, &expose_hook, &rt);
		mlx_hook(rt.window, 2, 1L<<0, &key_hook, &rt);
		mlx_loop(rt.mlx);
	}
	return (0);
}
