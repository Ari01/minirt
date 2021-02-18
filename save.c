/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:02:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 11:13:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

	j = rt->height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < rt->width)
		{
			src = rt->img.addr + (j * rt->img.line_length + i * (rt->img.bits_per_pixel / 8));
			color = *(unsigned int *)src;
			rgb = (unsigned char)(color & 0xFF);
			write(fd, &rgb, sizeof(rgb));
			rgb = (unsigned char)((color >> 8 & 0xFF));
			write(fd, &rgb, sizeof(rgb));
			rgb = (unsigned char)((color >> 16 & 0xFF));
			write(fd, &rgb, sizeof(rgb));
			i++;
		}
		write_pitch(pitch, fd);
		j--;
	}
}

void		write_header(t_rt *rt, int fd)
{
	t_bmp_header	head;
	int				pitch;
	int				data_size;
	char			*corrpitch;

	ft_memset(&head, 0, sizeof(t_bmp_header));
	head.signature[0] = 'B';
	head.signature[1] = 'M';
	head.offsetim = (int)sizeof(t_bmp_header);
	head.im_header.size_imhead = (int)sizeof(t_image_header);
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
