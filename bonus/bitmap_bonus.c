/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:04:44 by tjung             #+#    #+#             */
/*   Updated: 2021/03/17 22:30:00 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		write_bmp_data(t_game *g, int fd, unsigned int **buffer)
{
	unsigned char	byte[4];
	int				i;
	int				j;

	i = g->scr.size.y;
	while (--i >= 0)
	{
		j = -1;
		while (++j < g->scr.size.x)
		{
			byte[0] = (unsigned char)(buffer[i][j] % 256);
			byte[1] = (unsigned char)(buffer[i][j] / 256 % 256);
			byte[2] = (unsigned char)(buffer[i][j] / 256 / 256 % 256);
			byte[3] = (unsigned char)(buffer[i][j] / 256 / 256 / 256);
			write(fd, byte, 4);
		}
	}
}

static void		write_bmp_info(t_game *g, int fd)
{
	unsigned char	header[40];
	int				s;

	s = 0;
	while (s < 40)
		header[s++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	s = g->scr.size.x;
	header[4] = (unsigned char)(s % 256);
	header[5] = (unsigned char)(s / 256 % 256);
	header[6] = (unsigned char)(s / 256 / 256 % 256);
	header[7] = (unsigned char)(s / 256 / 256 / 256);
	s = g->scr.size.y;
	header[8] = (unsigned char)(s % 256);
	header[9] = (unsigned char)(s / 256 % 256);
	header[10] = (unsigned char)(s / 256 / 256 % 256);
	header[11] = (unsigned char)(s / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	s = g->scr.size.x * g->scr.size.y;
	header[20] = (unsigned char)(s % 256);
	header[21] = (unsigned char)(s / 256 % 256);
	header[22] = (unsigned char)(s / 256 / 256 % 256);
	header[23] = (unsigned char)(s / 256 / 256 / 256);
	write(fd, header, 40);
}

static void		write_bmp_header(t_game *g, int fd)
{
	unsigned char	header[14];
	int				s;

	s = 0;
	while (s < 14)
		header[s++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	s = g->scr.size.x * g->scr.size.y * 4 + 54;
	header[2] = (unsigned char)(s % 256);
	header[3] = (unsigned char)(s / 256 % 256);
	header[4] = (unsigned char)(s / 256 / 256 % 256);
	header[5] = (unsigned char)(s / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

static int		draw_bmp_first_screen(t_game *g, unsigned int **buffer)
{
	double			z_depth[g->scr.size.x];

	set_plane_values(g);
	print_image_to_buffer(g, buffer, z_depth);
	print_sprite_to_buffer(g, buffer, z_depth);
	make_time_bar(g, g->buffer, 0);
	return (0);
}

int				make_bitmap(t_game *g, unsigned int **buffer)
{
	int		fd;

	draw_bmp_first_screen(g, buffer);
	fd = open("bitmap_bonus.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write_bmp_header(g, fd);
	write_bmp_info(g, fd);
	write_bmp_data(g, fd, buffer);
	close(fd);
	close_cub3d(g, 0);
	return (0);
}
