/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:30:06 by user42            #+#    #+#             */
/*   Updated: 2020/12/15 20:49:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <stdio.h>
t_rt		init_rt(int width, int height)
{
	t_rt rt;

	rt.width = width;
	rt.height = height;
	rt.mlx = mlx_init();
	rt.window = mlx_new_window(rt.mlx, width, height, "minirt");
	rt.img.img = mlx_new_image(rt.mlx, width, height);
	rt.img.addr = mlx_get_data_addr(
					rt.img.img, 
					&rt.img.bits_per_pixel, 
					&rt.img.line_length, 
					&rt.img.endian);
	return (rt);
}

void		img_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	x = 600/2 + x;
	y = 600/2 - y - 1;
	if (x < 0 || x >= 600 || y < 0 || y >= 600)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_color		new_color(double r, double g, double b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

int			color_to_trgb(t_color color)
{
	return (0 << 24 | (int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

t_color		color_mul(double coef, t_color color)
{
	color.r *= coef;
	color.g *= coef;
	color.b *= coef;
	return (color);
}

t_vector	new_vector(double x, double y, double z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_ray		new_ray(t_vector start, t_vector dir)
{
	t_ray ray;

	ray.start = start;
	ray.dir = dir;
	return (ray);
}

t_sphere	new_sphere(t_vector pos, double radius, t_color color)
{
	t_sphere sp;

	sp.pos = pos;
	sp.radius = radius;
	sp.color = color;
	return (sp);
}

t_viewport	new_viewport(int width, int height, double distance)
{
	t_viewport v;

	v.width = width;
	v.height = height;
	v.distance = distance;
	return (v);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vector	vector_scale(double scale, t_vector v)
{
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	return (v);
}

double		vector_mul(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		vector_len(t_vector v)
{
	return (sqrtf(vector_mul(v,v)));
}

t_vector	canvas_to_viewport(t_rt *rt, double x, double y)
{
	
	return (new_vector(
				x * rt->viewport.width / rt->width, 
				y * rt->viewport.height / rt->height, 
				rt->viewport.distance));
}

double		intersect_ray_sphere(t_ray viewray, t_sphere sp)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_vector	dist;

	dist = vector_sub(viewray.start, sp.pos);
	a = vector_mul(viewray.dir, viewray.dir);
	b = 2 * vector_mul(dist, viewray.dir);
	c = vector_mul(dist, dist) - sp.radius * sp.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (100000.0);
	return (min((-b + sqrtf(discriminant)) / (2 * a), (-b - sqrtf(discriminant)) / (2 * a)));
}

double		add_light(t_ray viewray, t_light *light, t_vector sp_center, double t)
{
	t_vector	intersection;
	t_vector	normal;
	t_vector	light_dir;
	double		res;
	int			i;

	intersection = vector_add(viewray.start, vector_scale(t, viewray.dir));
	normal = vector_sub(intersection, sp_center);
	normal = vector_scale(1.0f / vector_len(normal), normal);
	res = 0;
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			res += light[i].intensity;
		else
		{
			if (i == 1)
				light_dir = vector_sub(light[i].pos, intersection);
			else
				light_dir = light[i].pos;
			if (vector_mul(normal, light_dir) > 0)
			{
				res += (vector_mul(normal, light_dir) * light[i].intensity) / (vector_len(normal) * vector_len(light_dir));
			}
		}
		i++;
	}
	return (res);
}

t_color		trace_ray(t_ray viewray, t_sphere* sp, t_light *light)
{
	double		closest_t;
	double		t;
	t_sphere	*closest_sphere;
	int			i;

	closest_t = 100000.0;
	closest_sphere = NULL;
	i = 0;
	while (i < 4)
	{
		t = intersect_ray_sphere(viewray, sp[i]);
		if (t < closest_t)
		{
			closest_t = t;
			closest_sphere = &sp[i];
		}
		i++;
	}
	if (closest_sphere)
		return (color_mul(add_light(viewray, light, closest_sphere->pos, t), closest_sphere->color));
	return (new_color(0, 0, 0));
}

int		exit_prog(t_rt *rt)
{
	mlx_clear_window(rt->mlx, rt->window);
	mlx_destroy_window(rt->mlx, rt->window);
	exit(EXIT_SUCCESS);
}

t_light	new_light(t_vector pos, t_color color, double intensity)
{
	t_light l;

	l.pos = pos;
	l.color = color;
	l.intensity = intensity;
	return (l);
}

int main()
{
	t_rt rt;
	t_viewport viewport;
	t_sphere sp[4];
	t_ray viewray;
	t_color color;
	t_light light[3];
	int x;
	int y;

	rt = init_rt(600, 600);
	viewport = new_viewport(1, 1, 1.0);
	rt.viewport = viewport;
	sp[0] = new_sphere(new_vector(0, -1, 3), 1, new_color(255, 0, 0));
	sp[1] = new_sphere(new_vector(2, 0, 4), 1, new_color(0, 0, 255));
	sp[2] = new_sphere(new_vector(-2, 0, 4), 1, new_color(0, 255, 0));
	sp[3] = new_sphere(new_vector(0, -5001, 0), 5000, new_color(255, 255, 0));
	viewray = new_ray(new_vector(0, 0, 0), new_vector(0, 0, 1));
	light[0] = new_light(new_vector(2, 1, 0), new_color(255, 255, 255), 0.2);
	light[1] = new_light(new_vector(2, 1, 0), new_color(255, 255, 255), 0.6);
	light[2] = new_light(new_vector(1, 4, 4), new_color(255, 255, 255), 0.2);

	y = -rt.height/2;
	while (y < rt.height/2)
	{
		x = -rt.width/2;
		while (x < rt.width/2)
		{
			viewray.dir = canvas_to_viewport(&rt, x, y);
			color = trace_ray(viewray, sp, light);
			img_pixel_put(&rt.img, x, y, color_to_trgb(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt.mlx, rt.window, rt.img.img, 0, 0);
	mlx_hook(rt.window, 33, 1L<<0, &exit_prog, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
