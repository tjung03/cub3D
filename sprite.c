/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:30:01 by tjung             #+#    #+#             */
/*   Updated: 2021/03/13 01:28:45 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(int *order, double *dist, int amount)
{
	double	tmp_dist;
	int		tmp_order;
	int		i;
	int		j;

	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp_dist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = tmp_dist;
				tmp_order = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp_order;
			}
		}
	}
}

int		print_sprite_to_window(t_game *g, double *z_depth)
{
	int				sprite_order[g->map.spr];
	double			sprite_distance[g->map.spr];
	int				i;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_scr_x;
	int				v_move_scr;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				tex_x;
	int				y;
	int				d;
	int				tex_y;
	unsigned int	color;

	i = -1;
	while (++i < g->map.spr)
	{
		sprite_order[i] = i;
		sprite_distance[i] =
					(g->p.pos.x - g->spr[i].x) * (g->p.pos.x - g->spr[i].x)
					+ (g->p.pos.y - g->spr[i].y) * (g->p.pos.y - g->spr[i].y);
	}
	sort_sprites(sprite_order, sprite_distance, g->map.spr);
	i = -1;
	while (++i < g->map.spr)
	{
		sprite_x = g->spr[sprite_order[i]].x - g->p.pos.x;
		sprite_y = g->spr[sprite_order[i]].y - g->p.pos.y;
		inv_det =
			1.0 / (g->p.plane.x * g->p.dir.y - g->p.dir.x * g->p.plane.y);
		transform_x =
			inv_det * (g->p.dir.y * sprite_x - g->p.dir.x * sprite_y);
		transform_y =
			inv_det * (-g->p.plane.y * sprite_x + g->p.plane.x * sprite_y);
		sprite_scr_x =
			(int)(g->scr.size.x / 2) * (1 + transform_x / transform_y);
		v_move_scr = (int)(V_MOVE / transform_y);
		sprite_height = abs((int)(g->scr.size.y / transform_y)) / V_DIV;
		draw_start_y = -sprite_height / 2 + g->scr.size.y / 2 + v_move_scr;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + g->scr.size.y / 2 + v_move_scr;
		if (draw_end_y >= g->scr.size.y)
			draw_end_y = g->scr.size.y - 1;
		sprite_width = abs((int)(g->scr.size.y / transform_y)) / U_DIV;
		draw_start_x = -sprite_width / 2 + sprite_scr_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_scr_x;
		if (draw_end_x >= g->scr.size.x)
			draw_end_x = g->scr.size.x - 1;
		stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_scr_x))
													* 64 / sprite_width) / 256;
			if (transform_y > 0 && transform_y < z_depth[stripe]
						&& stripe > 0 && stripe < g->scr.size.x)
			{
				y = draw_start_y;
				while (y < draw_end_y)
				{
					d = (y - v_move_scr) * 256 - g->scr.size.y * 128
											+ sprite_height * 128;
					tex_y = ((d * 64) / sprite_height) / 256;
					color = g->tex.i[64 * tex_y + tex_x];
					if ((color & 0x00FFFFFF) != 0)
						draw_pixel(g, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
	}
	return (0);
}
