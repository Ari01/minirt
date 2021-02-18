/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:02:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 08:59:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#pragma pack(1)

void		write_pitch(int pitch, int fd)
{
	int				i;
	unsigned char	zero;

	zero = 0;
	i = 0;
	while (i < pitch)
	{
		write(fd, &zero, sizeof(zero));
		i++;
	}
}

void		write_color(t_rt *rt, int pitch, int fd)
{
	int				i;
	int				j;
	int				color;
	unsigned char	rgb;
	char			*src;

	j = 0;
	while (j < rt->width)
	{
		i = 0;
		while (i < rt->height)
		{
			src = rt->img.addr + (i * rt->img.line_length + j * (rt->img.bits_per_pixel / 8));
			color = *(unsigned int *)src;
			rgb = (unsigned char)(color & 0xFF);
			//printf("b = %d\n", rgb);
			write(fd, &rgb, sizeof(rgb));
			rgb = (unsigned char)((color >> 8 & 0xFF));
			//printf("g = %d\n", rgb);
			write(fd, &rgb, sizeof(rgb));
			rgb = (unsigned char)((color >> 16 & 0xFF));
			//printf("r = %d\n", rgb);
			write(fd, &rgb, sizeof(rgb));
			i++;
		}
		write_pitch(pitch, fd);
		j++;
	}
}

void			write_header(t_rt *rt, int fd)
{
	t_bmp_header	head;
	int				pitch;
	int				data_size;
	char			*corrpitch;

	ft_memset(&head, 0, sizeof(t_bmp_header));
	head.signature[0] = 'B';
	head.signature[1] = 'M';
	head.offsetim = sizeof(t_bmp_header);
	head.im_header.size_imhead = sizeof(t_image_header);
	head.im_header.width = (int)rt->width;
	head.im_header.height = (int)rt->height;
	head.im_header.nbplans = 1;
	head.im_header.bpp = 24;
	corrpitch = "0321";
	pitch = corrpitch[(3 * head.im_header.width) % 4] - '0';
	data_size = 3 * head.im_header.height * head.im_header.width;
	data_size += head.im_header.height * pitch;
	head.im_header.size_im = data_size;
	head.size = head.offsetim + head.im_header.size_im;
	printf("size = %d\n", head.size);
	write(fd, &head, sizeof(t_bmp_header));
	write_color(rt, pitch, fd);
}

void		img_to_bmp(t_rt *rt, char *path)
{
	int				fd;
	char			*fullpath;

	fullpath = ft_strjoin("images/", path);
	fd = open(fullpath, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_perror(errno);
	write_header(rt, fd);
	close(fd);
}

/*
void		write_default_value(int fd, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putstr_fd("00", fd);
		i++;
	}
}

void		write_hex(int fd, char *hex)
{
	int		len;

	len = ft_strlen(hex);
	if (len == 1)
	//{
		ft_putstr_fd("0", fd);
	ft_putstr_fd(hex, fd);
		write(fd, &hex[0], 1);
	}
	else if (len > 2)
	{
		write_hex(fd, hex + 2);
		write(fd, &hex[0], 1);
		write(fd, &hex[1], 1);
	}
	else
	{
		write(fd, &hex[0], 1);
		write(fd, &hex[1], 1);
	}
}

void		write_bmp_header(t_rt *rt, int fd)
{
	char	*hex;

	ft_putstr_fd("424D", fd);
	write_default_value(fd, 8);
	ft_putstr_fd("36", fd);
	write_default_value(fd, 3);
	ft_putstr_fd("28", fd);
	write_default_value(fd, 3);
	hex = ft_dec_to_hex(rt->width);
	write_hex(fd, hex);
	write_default_value(fd, 3 - ft_strlen(hex) / 3);
	free(hex);
	hex = ft_dec_to_hex(rt->height);
	write_hex(fd, hex);
	write_default_value(fd, 3 - ft_strlen(hex) / 3);
	free(hex);
	ft_putstr_fd("0100", fd);
	hex = ft_dec_to_hex(rt->img.bits_per_pixel);
	write_hex(fd, hex);
	write_default_value(fd, 3 - ft_strlen(hex) / 3);
	free(hex);
	write_default_value(fd, 24);
}

void		write_color(int color, int fd)
{
	char	*hex;
	char	hex2[3];

	hex = ft_dec_to_hex(color);
	hex2[0] = hex[0];
	hex2[1] = hex[1];
	hex2[2] = '\0';
	free(hex);
	printf("%s\n", hex2);
	write_hex(fd, hex2);
}

void		write_pixel_data(t_rt *rt, int fd)
{
	char			*dst;
	unsigned int	color;
	int				x;
	int				y;

	x = 0;
	(void)fd;
	while (x < rt->width)
	{
		y = 0;
		while (y < rt->height)
		{
			dst = rt->img.addr + (y * rt->img.line_length + x * (rt->img.bits_per_pixel / 8));
			color = *(int *)dst;
			write_color(color & (0xFF << 24), fd);
			write_color(color & (0xFF << 16), fd);
			write_color(color & (0xFF << 8), fd);
			write_color(color & (0xFF), fd);
			y++;
		}
		x++;
	}
}

void		img_to_bmp(t_rt *rt, char *path)
{
	int		fd;
	char	*fullpath;

	fullpath = ft_strjoin("images/", path);
	fd = open(fullpath, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_perror(errno);
	write_bmp_header(rt, fd);
	write_pixel_data(rt, fd);
	free(fullpath);
	close(fd);
}*/
