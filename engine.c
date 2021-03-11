/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:46:24 by tjung             #+#    #+#             */
/*   Updated: 2021/03/11 18:36:21 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			calculate_tex_pos(t_game *g, int line_h, double *step)
{
	if (g->rc.side == 0)
		g->rc.wall_x = g->p.pos.y + g->rc.perp_wall_dist * g->rc.ray_dir.y;
	else
		g->rc.wall_x = g->p.pos.x + g->rc.perp_wall_dist * g->rc.ray_dir.x;
	g->rc.wall_x -= floor(g->rc.wall_x);
	g->tex.tex_x = (int)(g->rc.wall_x * 64.0);
	if ((g->rc.side == 0 && g->rc.ray_dir.x > 0)
			|| (g->rc.side == 1 && g->rc.ray_dir.y < 0))
		g->tex.tex_x = 64 - g->tex.tex_x - 1;
	(*step) = 1.0 * 64 / line_h;
	g->rc.draw_start = g->scr.size.y / 2 - line_h / 2;
	g->rc.draw_end = g->scr.size.y / 2 + line_h / 2;
	if (g->rc.draw_start < 0)
		g->rc.draw_start = 0;
	if (g->rc.draw_end >= g->scr.size.y)
		g->rc.draw_end = g->scr.size.y - 1;
	g->tex.tex_pos =
		(g->rc.draw_start - (g->scr.size.y / 2) + (line_h / 2)) * (*step);
}

unsigned int	get_color(t_game *g)
{
	unsigned int	color;

	if (g->rc.side == 0)
	{
		if (g->rc.hit_x < g->p.pos.x)
			color = g->tex.w[64 * g->tex.tex_y + g->tex.tex_x];
		else
			color = g->tex.e[64 * g->tex.tex_y + g->tex.tex_x];
	}
	else
	{
		if (g->rc.hit_y < g->p.pos.y)
			color = g->tex.n[64 * g->tex.tex_y + g->tex.tex_x];
		else
			color = g->tex.s[64 * g->tex.tex_y + g->tex.tex_x];
	}
	if (g->rc.side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

int				print_image_to_window(t_game *g)
{
	double			step;
	int				x;
	int				y;

	x = -1;
	while (++x < g->scr.size.x)
	{
		calculate_tex_pos(g, get_line_height(g, x), &step);
		y = -1;
		while (++y < g->scr.size.y)
		{
			if (y < g->rc.draw_start)
				draw_pixel(g, x, y, g->tex.c);
			else if (y >= g->rc.draw_start && y <= g->rc.draw_end)
			{
				g->tex.tex_y = (int)g->tex.tex_pos & (64 - 1);
				g->tex.tex_pos += step;
				draw_pixel(g, x, y, get_color(g));
			}
			else
				draw_pixel(g, x, y, g->tex.f);
		}
	}
	return (0);
}

int				start_engine(t_game *g)
{
	set_plane_values(g);
	print_image_to_window(g);
	return (0);
}
