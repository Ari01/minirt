/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:02:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 17:08:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		write_default_value(int fd, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putstr_fd("00 ", fd);
		i++;
	}
}

void		write_hex(int fd, char *hex)
{
	int		len;

	len = ft_strlen(hex);
	if (len == 1)
	{
		ft_putstr_fd("0", fd);
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
	ft_putstr_fd(" ", fd);
}

void		write_bmp_header(t_rt *rt, int fd)
{
	char	*hex;

	ft_putstr_fd("42 4D ", fd);
	write_default_value(fd, 8);
	ft_putstr_fd("36 ", fd);
	write_default_value(fd, 3);
	ft_putstr_fd("28 ", fd);
	write_default_value(fd, 3);
	hex = ft_dec_to_hex(rt->width);
	write_hex(fd, hex);
	write_default_value(fd, 3 - ft_strlen(hex) / 3);
	free(hex);
	hex = ft_dec_to_hex(rt->height);
	write_hex(fd, hex);
	write_default_value(fd, 3 - ft_strlen(hex) / 3);
	free(hex);
	ft_putstr_fd("01 00 ", fd);
	hex = ft_dec_to_hex(rt->img.bits_per_pixel);
	write_hex(fd, hex);
	write_default_value(fd, 3 - ft_strlen(hex) / 3);
	free(hex);
	write_default_value(fd, 24);
}

void		write_pixel_data(t_rt *rt, int fd)
{
	char			*dst;
	char			*hex;
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
			color = *(unsigned int *)dst;
			color = (color & (0xFF << 8));
			hex = ft_dec_to_hex(color / 100);
			write_hex(fd, hex);
			free(hex);
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
