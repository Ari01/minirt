#include "mlx.h"
#include "minirt.h"

#include <stdio.h>
#include <stdlib.h>

int		exit_prog(t_rt *rt)
{
	mlx_clear_window(rt->mlx, rt->window);
	mlx_destroy_window(rt->mlx, rt->window);
	exit(EXIT_SUCCESS);
}

int		get_key_press(int key, t_rt *rt)
{
	printf("key pressed = %d\n", key);
	if (key == ESCAPE)
	{
		printf("yo\n");
		exit_prog(rt);
	}
	return (1);
}

int		mouse_press(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	(void)button;
	(void)rt;

	printf("mouse press\n");
	return (0);
}

int		mouse_release(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	(void)button;
	(void)rt;

	printf("mouse release\n");
	return (0);
}

int		get_mouse_pos(int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	(void)rt;
	printf("mouse pos\n");
	return (0);
}

int		main()
{
	t_rt	rt;
	
	rt.mlx = mlx_init();
	if (!rt.mlx)
		return (1);
	rt.window = mlx_new_window(rt.mlx, 1320, 960, "Hello World");
	if (!rt.window)
		return (1);
	printf("yo\n");
	mlx_do_key_autorepeatoff(rt.mlx);
	mlx_hook(rt.window, 2, 0, get_key_press, &rt);
	mlx_hook(rt.window, 4, 0, mouse_press, &rt);
	mlx_hook(rt.window, 5, 0, mouse_release, &rt);
	mlx_hook(rt.window, 6, 0, get_mouse_pos, &rt);
	mlx_hook(rt.window, 17, 0, exit_prog, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
