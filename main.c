/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:45:57 by user42            #+#    #+#             */
/*   Updated: 2020/12/25 00:24:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rt	init_rt(int width, int height)
{
	t_rt rt;

	rt.width = width;
	rt.height = height;
	rt.mlx = mlx_init();
	rt.window = mlx_new_window(rt.mlx, width, height, "minirt");
	rt.img.img = mlx_new_image(rt.mlx, width, height);
	rt.img.addr = mlx_get_data_addr(rt.img.img,
									&rt.img.bits_per_pixel,
									&rt.img.line_length,
									&rt.img.endian);
	return (rt);
}

void	img_pixel_put(t_rt *rt, int x, int y, int color)
{
	char *dst;

	//x = rt->width / 2 + x;
	//y = rt->height / 2 - y - 1;
	if (x < 0 || x >= rt->width || y < 0 || y >= rt->height)
		return ;
	dst = rt->img.addr + (y * rt->img.line_length + x *(rt->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_vector	new_vector(double x, double y, double z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
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

t_vector	vector_mul(double x, t_vector v)
{
	v.x *= x;
	v.y *= x;
	v.z *= x;
	return (v);
}

double		vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		vector_len(t_vector v)
{
	return (sqrtf(vector_dot(v, v)));
}

t_ray		new_ray(t_vector start, t_vector dir)
{
	t_ray r;

	r.start = start;
	r.dir = dir;
	return (r);
}

t_sphere	new_sphere(t_vector center, double radius, double specular, t_color color)
{
	t_sphere s;

	s.center = center;
	s.radius = radius;
	s.color = color;
	s.specular = specular;
	return (s);
}

t_viewport	new_viewport(double width, double height, double distance)
{
	t_viewport v;

	v.width = width;
	v.height = height;
	v.distance = distance;
	return (v);
}

t_color	new_color(double r, double g, double b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

int		color_to_trgb(t_color color)
{
	return (0 << 24 | (int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

t_color	color_mul(double x, t_color color)
{
	color.r *= x;
	color.g *= x;
	color.b *= x;
	return (color);
}

t_color	color_clamp(t_color color)
{
	color.r = MIN(255, MAX(0, color.r));
	color.g = MIN(255, MAX(0, color.g));
	color.b = MIN(255, MAX(0, color.b));
	return (color);
}

t_light	new_light(t_vector pos, double intensity, t_color color)
{
	t_light l;

	l.pos = pos;
	l.intensity = intensity;
	l.color = color;
	return (l);
}

t_scene	new_scene(t_sphere *sphere, t_light *light)
{
	t_scene s;

	s.sphere = sphere;
	s.light = light;
	return (s);
}

#include <stdio.h>
void	intersect_ray_sphere(double *t1, double *t2, t_ray viewray, t_sphere sp)
{
	t_vector	dist;
	double		a;
	double		b;
	double		c;
	double		disc;

	dist = vector_sub(viewray.start, sp.center);
	a = vector_dot(viewray.dir, viewray.dir);
	b = 2 * vector_dot(dist, viewray.dir);
	c = vector_dot(dist, dist) - sp.radius * sp.radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		*t1 = 100000.0;
		*t2 = 100000.0;
	}
	else
	{
		*t1 = (-b + sqrtf(disc)) / (2 * a);
		*t2 = (-b - sqrtf(disc)) / (2 * a);
	}
}

t_vector	get_intersection(t_ray viewray, double intersection)
{
	return (vector_add(viewray.start, vector_mul(intersection, viewray.dir)));
}

t_vector	get_normal(t_vector intersection, t_vector center)
{
	t_vector normal;

	normal = vector_sub(intersection, center);
	normal = vector_mul(1 / vector_len(normal), normal);
	return (normal);
}

int		get_closest_intersection(t_scene *scene, t_ray viewray, double *closest_t, double t_min, double t_max)
{
	double		t1;
	double		t2;
	int			i;
	int			closest_sphere;

	*closest_t = 100000.0;
	closest_sphere = -1;
	i = 0;
	while (i < 4)
	{
		intersect_ray_sphere(&t1, &t2, viewray, scene->sphere[i]);
		if (t1 > t_min && t1 < t_max && t1 < *closest_t)
		{
			*closest_t = t1;
			closest_sphere = i;
		}
		if (t2 > t_min && t2 < t_max && t2 < *closest_t)
		{
			*closest_t = t2;
			closest_sphere = i;
		}
		i++;
	}
	return (closest_sphere);
}

double	compute_light(t_scene *scene, t_sphere sp, t_vector intersection, t_vector viewray_dir)
{
	double		intensity;
	int			i;
	t_vector	light_vector;
	t_vector	normal;
	double		n_dot_l;
	double		t;
	double		t_max;

	normal = get_normal(intersection, sp.center);
	intensity = 0.0;
	i = 0;
	while (i < 3)
	{
		if (!i)
			intensity += scene->light[i].intensity;
		else
		{
			if (i == 1)
			{
				light_vector = vector_sub(scene->light[i].pos, intersection);
				t_max = 1;
			}
			else
			{
				light_vector = scene->light[i].pos;
				t_max = 100000.0;
			}
			if (get_closest_intersection(scene, new_ray(intersection, light_vector), &t, 0.001, t_max) == -1)
			{
				n_dot_l = vector_dot(normal, light_vector);
				if (n_dot_l > 0)
					intensity += scene->light[i].intensity * n_dot_l / (vector_len(normal) * vector_len(light_vector));
				if (sp.specular != -1)
				{
					t_vector reflect;
					double r_dot_v;

					reflect = vector_sub(vector_mul(2 * vector_dot(normal, light_vector), normal), light_vector);
					r_dot_v = vector_dot(reflect, viewray_dir);
					if (r_dot_v > 0)
						intensity += scene->light[i].intensity * pow(r_dot_v / (vector_len(reflect) * vector_len(viewray_dir)), sp.specular);
				}
			}
		}
		i++;
	}
	return (intensity);
}

t_color	trace_ray(t_ray viewray, t_scene *scene)
{
	double		closest_t;
	t_sphere	closest_sphere;	
	t_vector	intersection;
	t_vector	viewray_dir;
	int			i;

	i = get_closest_intersection(scene, viewray, &closest_t, 1, 100000.0);
	if (i != -1)
	{
		closest_sphere = scene->sphere[i];
		intersection = get_intersection(viewray, closest_t);
		viewray_dir = vector_mul(-1, viewray.dir);
		return (color_mul(compute_light(scene, closest_sphere, intersection, viewray_dir), closest_sphere.color));
	}
	return (new_color(0, 0, 0));
}

int	exit_prog(t_rt *rt)
{
	mlx_clear_window(rt->mlx, rt->window);
	mlx_destroy_window(rt->mlx, rt->window);
	exit(EXIT_SUCCESS);
}

t_vector	matrix_multiply(t_vector v, t_vector matrix[3])
{
	v.x = v.x * matrix[0].x + v.y * matrix[0].y + v.z * matrix[0].z;
	v.y = v.x * matrix[1].x + v.y * matrix[1].y + v.z * matrix[1].z;
	v.z = v.x * matrix[2].x + v.y * matrix[2].y + v.z * matrix[2].z;
	return (v);
}

double		deg_to_rad(double deg)
{
	return ((deg * M_PI) / 180);
}

t_vector	rotate_y(t_vector v, double angle)
{
	angle = deg_to_rad(angle);
	v.x = v.x * cos(angle) - v.z * sin(angle);
	v.z = v.z * cos(angle) + v.x * sin(angle);
	return(v);
}

t_vector	img_to_viewport(t_rt *rt, t_ray viewray, double x, double y)
{
	double		aspect_ratio;
	double		scale;
	double		max;
	double		min;

	max = MAX(rt->width, rt->height);
	min = MIN(rt->width, rt->height);
	aspect_ratio = max / min;
	scale = tan(M_PI * 70 * 0.5 / 180);
	x = (2 * (x + 0.5) / (double)rt->width - 1) * scale;
	y = (1 - 2 * (y + 0.5) / (double)rt->height) * scale;
	if (rt->width > rt->height)
		x *= aspect_ratio;
	else if (rt->height > rt->width)
		y *= aspect_ratio;
	viewray.dir = new_vector(x, y, 1);
	return (viewray.dir);
}

void	render(t_rt *rt, t_vector (*rotate)(t_vector, double), double rad)
{
	int i;
	int j;
	t_color color;

	j = 0;
	while (j < rt->height)
	{
		i = 0;
		while (i < rt->width)
		{
			rt->object->camera->viewray.dir = img_to_viewport(rt, rt->object->camera->viewray, i, j);
			if (rotate)
				rt->object->camera->viewray.dir = rotate(rt->object->camera->viewray.dir, rad);
			rt->object->camera->viewray.dir = vector_mul(1 / vector_len(rt->object->camera->viewray.dir), rt->object->camera->viewray.dir);
			rt->scene.viewray = rt->object->camera->viewray;
			color = trace_ray(rt->object->camera->viewray, &rt->scene);
			img_pixel_put(rt, i, j, color_to_trgb(color_clamp(color)));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(rt->mlx, rt->window, rt->img.img, 0, 0);
}

int key_hook(int key, t_rt *rt)
{
	static double rad;

	if (key == ESCAPE)
		exit_prog(rt);
	if (key == RIGHT)
	{
		rad -= 10;
		render(rt, &rotate_y, rad);
	}
	if (key == LEFT)
	{
		rad += 10;
		render(rt, &rotate_y, rad);
	}
	if (key == UP)
	{
		rt->object->camera->viewray.start.z += 1;
		render(rt, NULL, 0);
	}
	if (key == DOWN)
	{
		rt->object->camera->viewray.start.z -= 1;
		render(rt, NULL, 0);
	}

	return (1);
}

int main()
{
	t_rt			rt;
	t_ray			viewray;
	t_sphere		sphere[4];
	t_light			light[3];
	t_color			color;
	t_scene			scene;
	t_object_set	set;
	t_camera		camera;
	int				x;
	int				y;
	//double			rad;
	//t_vector		y_rotation_matrix[3];

	rt = init_rt(600, 800);
	/*rad = -0.174533;
	y_rotation_matrix[0] = new_vector(cos(rad), 0, sin(rad));
	y_rotation_matrix[1] = new_vector(0, 1, 0);
	y_rotation_matrix[2] = new_vector(-sin(rad), 0, cos(rad));*/
	viewray = new_ray(new_vector(0, 0, -1), new_vector(0, 0, 1));
	sphere[0] = new_sphere(new_vector(0, -1, 3), 1, 500, new_color(255, 0, 0));
	sphere[1] = new_sphere(new_vector(2, 0, 4), 1, 500, new_color(0, 0, 255));
	sphere[2] = new_sphere(new_vector(-2, 0, 4), 1, 10, new_color(0, 255, 0));
	sphere[3] = new_sphere(new_vector(0, -5001, 0), 5000, 1000, new_color(255, 255, 0));
	light[0] = new_light(new_vector(0, 0, 0), 0.2, new_color(255, 255, 255));
	light[1] = new_light(new_vector(2, 1, 0), 0.6, new_color(255, 255, 255));
	light[2] = new_light(new_vector(1, 4, 4), 0.2, new_color(255, 255, 255));
	scene = new_scene(sphere, light);
	set.light = light;
	set.sphere = sphere;
	y = 0;
	while (y < rt.height)
	{
		x = 0;
		while (x < rt.width)
		{
			viewray.dir = img_to_viewport(&rt, viewray, x, y);
			viewray.dir = vector_mul(1 / vector_len(viewray.dir), viewray.dir);
			camera.viewray = viewray;
			camera.fov = 70;
			rt.object = &set;
			rt.object->camera = &camera;
			rt.scene = scene;
			color = trace_ray(rt.object->camera->viewray, &rt.scene);
			img_pixel_put(&rt, x, y, color_to_trgb(color_clamp(color)));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt.mlx, rt.window, rt.img.img, 0, 0);
	mlx_hook(rt.window, 33, 1L<<0, &exit_prog, &rt);
	mlx_hook(rt.window, 2, 1L<<0, &key_hook, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
