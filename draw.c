/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:20:14 by tjung             #+#    #+#             */
/*   Updated: 2021/02/23 05:18:40 by tjung            ###   ########.fr       */
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
