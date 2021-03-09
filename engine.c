/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:46:24 by tjung             #+#    #+#             */
/*   Updated: 2021/03/09 22:29:51 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				start_engine(t_game *g)
{
	int		line_h;
	int		x;

	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	unsigned int	color;
	int		draw_start;
	int		draw_end;

	set_plane_v(g);
	line_h = 0;
	x = -1;
	while (++x < g->scr.size.x)
	{
		get_line_h(g, x, &line_h);
		if (g->rc.side == 0)
			wall_x = g->p.pos.y + g->rc.perp_wall_dist * g->rc.ray_dir.y;
		else
			wall_x = g->p.pos.x + g->rc.perp_wall_dist * g->rc.ray_dir.x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * 64.0);
		if ((g->rc.side == 0 && g->rc.ray_dir.x > 0)
				|| (g->rc.side == 1 && g->rc.ray_dir.y < 0))
			tex_x = 64 - tex_x - 1;
		step = 1.0 * 64 / line_h;
		draw_start = g->scr.size.y / 2 - line_h / 2;
		draw_end = g->scr.size.y / 2 + line_h / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= g->scr.size.y)
			draw_end = g->scr.size.y - 1;
		tex_pos = (draw_start - (g->scr.size.y / 2) + (line_h / 2)) * step;
		y = -1;
		while (++y < g->scr.size.y)
		{
			if (y < draw_start)
				draw_pixel(g, x, y, g->tex.c);
			else if (y >= draw_start && y <= draw_end)
			{
				tex_y = (int)tex_pos & (64 - 1);
				tex_pos += step;
				if (g->rc.side == 0)
				{
					if (g->tex.hit_x < g->p.pos.x)
						color = g->tex.w[64 * tex_y + tex_x];
					else
						color = g->tex.e[64 * tex_y + tex_x];
				}
				else
				{
					if (g->tex.hit_y < g->p.pos.y)
						color = g->tex.n[64 * tex_y + tex_x];
					else
						color = g->tex.s[64 * tex_y + tex_x];
				}
				if (g->rc.side == 1)
					color = (color >> 1) & 8355711;
				draw_pixel(g, x, y, color);
			}
			else
				draw_pixel(g, x, y, g->tex.f);
		}
		//draw_vertical_l(g, line_h, x, 0x0000FF);
	}
	return (0);
}
