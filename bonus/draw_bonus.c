/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:20:14 by tjung             #+#    #+#             */
/*   Updated: 2021/03/19 03:56:14 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		draw_pixel(t_game *g, int x, int y, unsigned int color)
{
	char	*dst;
	int		offset;

	offset = y * g->scr.img.sl + x * (g->scr.img.bpp / 8);
	dst = g->scr.img.adr + offset;
	*(unsigned int *)dst = color;
}

void			draw_buffer(t_game *g, unsigned int **buffer)
{
	int		x;
	int		y;

	y = -1;
	while (++y < g->scr.size.y)
	{
		x = -1;
		while (++x < g->scr.size.x)
			draw_pixel(g, x, y, buffer[y][x]);
	}
}

void			draw_rectangle_to_buffer(t_game *g,
						int scale, unsigned int **buffer, unsigned int color)
{
	int		x;
	int		y;
	int		end_x;
	int		end_y;

	y = g->map.minimap.y * scale;
	end_y = y + scale;
	while (y < end_y)
	{
		x = g->map.minimap.x * scale;
		end_x = x + scale;
		while (x < end_x)
		{
			buffer[y][x] = color;
			x++;
		}
		y++;
	}
}

static void		calculate_scale(t_game *g, int *scale)
{
	*scale = g->scr.size.y / 100;
	if (*scale % 2 == 0)
		*scale += 1;
}

void			draw_map_to_buffer(t_game *g, unsigned int **buffer)
{
	int		scale;
	int		x;
	int		y;

	calculate_scale(g, &scale);
	y = -1;
	while (++y < g->map.size.y)
	{
		g->map.minimap.y = y;
		x = -1;
		while (++x < g->map.size.x)
		{
			g->map.minimap.x = x;
			if (g->map.tab[y][x] == '1')
				draw_rectangle_to_buffer(g, scale, buffer, 0x000000);
			else if (g->map.tab[y][x] != '1' && g->map.tab[y][x] != '2'
						&& g->map.tab[y][x] != '3' && g->map.tab[y][x] != ' ')
				draw_rectangle_to_buffer(g, scale, buffer, 0xFFFF00);
			else if (g->map.tab[y][x] == '2')
				draw_rectangle_to_buffer(g, scale, buffer, 0xFF00FF);
			else if (g->map.tab[y][x] == '3')
				draw_rectangle_to_buffer(g, scale, buffer, 0x0000FF);
		}
	}
	draw_player_to_buffer(g, scale, buffer);
}
