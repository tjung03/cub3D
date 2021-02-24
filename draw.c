/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:20:14 by tjung             #+#    #+#             */
/*   Updated: 2021/02/24 23:29:42 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_game *g, int x, int y, unsigned int color)
{
	char	*dst;
	int		offset;

	offset = y * g->img.size_line + x * (g->img.bpp / 8);
	dst = g->img.adr + offset;
	*(unsigned int *)dst = color;
}

void	draw_rec(t_game *g, int	x, int y, unsigned int color)
{
	int		i;
	int		j;

	i = x;
	while (i < 32)
	{
		j = y;
		while (j < 32)
		{
			draw_pixel(g, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *g)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;
	y = 0;
	i = 0;
	while (i < g->map.height)
	{
		j = 0;
		while (j < g->map.width)
		{
			if (g->map.tab[i][j] == '1')
				draw_rec(g, x, y, 0x00FF00);
			else if (g->map.tab[i][j] == '0')
				draw_rec(g, x, y, 0xFFFFFF);
			x += 32;
			j++;
		}
		y += 32;
		i++;
	}
}

void	draw_grid(t_game *g)
{
	int		x;
	int		y;

	x = 0;
	while (x < g->scr.width)
	{
		y = 0;
		while (y < g->scr.height)
		{
			draw_pixel(g, x, y, 0x000000);
			y++;
		}
		x += 32;
	}
	x = 0;
	while (x < g->scr.width)
	{
		y = 0;
		while (y < g->scr.height)
		{
			draw_pixel(g, y, x, 0x000000);
			y++;
		}
		x += 32;
	}
}
/*
void	draw_vertical_l(t_game *g, int len, int x, unsigned int color)
{
	int		draw_start;
	int		draw_end;
	int		y;

	draw_start = g->scr.height / 2 - len / 2;
	draw_end = g->scr.height / 2 + len / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= g->scr.height)
		draw_end = g->scr.height - 1;
	y = draw_start - 1;
	while (++y <= draw_end)
		draw_pixel(g, x, y, color);
}
*/