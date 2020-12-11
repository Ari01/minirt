#include "minirt.h"

#include <stdio.h>
int render_next_frame(t_rt *rt)
{
	(void)rt;
	return (0);
}

t_rt	*init_window(int width, int height, char *title)
{
	t_rt *rt;

	rt = malloc(sizeof(*rt));
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (NULL);
	rt->window = mlx_new_window(rt->mlx, width, height, title);
	if (!rt->window)
		return (NULL);
	rt->width = width;
	rt->height = height;
	return (rt);
}

void	wait_event(t_rt *rt)
{
	mlx_hook(rt->window, 17, 1L<<0, &exit_prog, rt);
	mlx_hook(rt->window, 2, 1L<<0, &get_key_press, rt);
	mlx_loop(rt->mlx);
}

void	img_pixel_put(t_rt *rt, int x, int y, int color)
{
	char *dst;

	dst = rt->img.addr + (y * rt->img.line_length + x * (rt->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		main()
{
	t_rt		*rt;
	t_sphere	sp;
	t_ray		ray;

	rt = init_window(500, 500, "minirt");
	if (!rt)
		return (0);
	rt->img.img = mlx_new_image(rt->mlx, 500, 500);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
								&rt->img.line_length, &rt->img.endian);
	sp = init_sphere(new_vector(255.0, 255.0, 0), 100);
	ray = init_ray(new_vector(0, 0, 0), new_vector(0, 0, 1));
	print_sphere(rt, sp, ray);
	mlx_put_image_to_window(rt->mlx, rt->window, rt->img.img, 0, 0);
	wait_event(rt);
	return (0);
}
