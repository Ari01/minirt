/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 11:13:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	check_save_arg(char *av)
{
	if (ft_strlen(av) != 5 || ft_strncmp(av, "-save", 5))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_rt rt;
	
	if (ac == 2 || (ac == 3 && check_save_arg(av[2])))
	{
		rt = set_rt(av[1]);
		set_mlx(&rt);
		printf("rendering image...\n");
		render(&rt);
		printf("rendering done.\n");
		if (ac == 3)
		{
			printf("saving image...\n");
			img_to_bmp(&rt, "test.bmp");
			printf("image saved.\n");
		}
		mlx_hook(rt.window, 33, 1L<<0, &exit_prog, &rt);
		mlx_hook(rt.window, 12, 1L<<15, &expose_hook, &rt);
		mlx_hook(rt.window, 2, 1L<<0, &key_hook, &rt);
		mlx_loop(rt.mlx);
	}
	return (0);
}
