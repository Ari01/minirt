/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:02:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 10:10:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	/*	write(fd, &hex[0], 1);
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
	}*/
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
}
