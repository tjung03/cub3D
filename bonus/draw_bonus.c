/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:20:14 by tjung             #+#    #+#             */
/*   Updated: 2021/03/17 17:55:59 by tjung            ###   ########.fr       */
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

void			draw_vertical_l(t_game *g, int len, int x, unsigned int color)
{
	int		y;

	g->rc.draw_start = g->scr.size.y / 2 - len / 2;
	g->rc.draw_end = g->scr.size.y / 2 + len / 2;
	if (g->rc.draw_start < 0)
		g->rc.draw_start = 0;
	if (g->rc.draw_end >= g->scr.size.y)
		g->rc.draw_end = g->scr.size.y - 1;
	y = -1;
	while (++y < g->scr.size.y)
	{
		if (y < g->rc.draw_start)
			draw_pixel(g, x, y, g->tex.c);
		else if (y >= g->rc.draw_start && y <= g->rc.draw_end)
			draw_pixel(g, x, y, color);
		else
			draw_pixel(g, x, y, g->tex.f);
	}
}
