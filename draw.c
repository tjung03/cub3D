/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:20:14 by tjung             #+#    #+#             */
/*   Updated: 2021/03/02 19:26:51 by tjung            ###   ########.fr       */
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

void	draw_irec(t_game *g, t_ivec vec, int scale, unsigned int color)
{
	int		i;
	int		j;

	i = vec.x;
	while (i < vec.x + scale)
	{
		j = vec.y;
		while (j < vec.y + scale)
		{
			draw_pixel(g, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_frec(t_game *g, t_fvec vec, int scale, unsigned int color)
{
	double	i;
	double	j;

	i = vec.x;
	while (i < vec.x + scale)
	{
		j = vec.y;
		while (j < vec.y + scale)
		{
			draw_pixel(g, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *g)
{
	t_ivec	map;
	int		i;
	int		j;

	map.y = 0;
	i = 0;
	while (i < g->map.size.y)
	{
		map.x = 0;
		j = 0;
		while (j < g->map.size.x)
		{
			if (g->map.tab[i][j] == '1')
				draw_irec(g, map, 32, 0x00FF00);
			else
				draw_irec(g, map, 32, 0xFFFFFF);
			map.x += 33;
			j++;
		}
		map.y += 33;
		i++;
	}
}

void	draw_player(t_game *g)
{
	t_fvec	player;

	player.x = g->p.pos.x * 33 - 1;
	player.y = g->p.pos.y * 33 - 1;
	draw_frec(g, player, 4, 0x0000FF);
}

void	draw_vertical_l(t_game *g, int len, int x, unsigned int color)
{
	int		draw_start;
	int		draw_end;
	int		y;

	draw_start = g->scr.size.y / 2 - len / 2;
	draw_end = g->scr.size.y / 2 + len / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= g->scr.size.y)
		draw_end = g->scr.size.y - 1;
	y = -1;
	while (++y < g->scr.size.y)
	{
		if (y < draw_start)
			draw_pixel(g, x, y, g->tex.c);
		else if (y >= draw_start && y <= draw_end)
			draw_pixel(g, x, y, color);
		else
			draw_pixel(g, x, y, g->tex.f);
	}
}
