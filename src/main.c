/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 10:11:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_save_arg(char *av)
{
	if (ft_strlen(av) != 5 || ft_strncmp(av, "-save", 5))
		return (0);
	return (1);
}

void	save_image(t_rt *rt, char *path)
{
	char	**split;
	char	*tmp;
	char	*filename;

	tmp = ft_strrchr(path, '/');
	split = ft_split(tmp, ".");
	filename = ft_strdup(*split);
	tmp = filename;
	filename = ft_strjoin(filename, ".bmp");
	printf("saving image...\n");
	img_to_bmp(rt, filename);
	printf("image saved.\n");
	free(tmp);
	string_array_free(split);
	free(filename);
}

int		main(int ac, char **av)
{
	t_rt rt;

	if (ac == 2 || (ac == 3 && check_save_arg(av[2])))
	{
		printf("parsing...\n");
		rt = set_rt(av[1]);
		printf("parsing done.\n");
		set_mlx(&rt);
		printf("rendering image...\n");
		render(&rt);
		printf("rendering done.\n");
		if (ac == 3)
			save_image(&rt, av[1]);
		mlx_hook(rt.window, 33, 1L << 0, &exit_prog, &rt);
		mlx_hook(rt.window, 12, 1L << 15, &expose_hook, &rt);
		mlx_hook(rt.window, 2, 1L << 0, &key_hook, &rt);
		mlx_loop(rt.mlx);
	}
	return (0);
}
