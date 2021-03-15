/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:11:57 by tjung             #+#    #+#             */
/*   Updated: 2021/03/16 05:10:32 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		descending_sort(int *order, double *dist, int amount)
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

void			sort_sprites(
						t_game *g, int *sprite_order, double *sprite_distance)
{
	int		i;

	i = -1;
	while (++i < g->map.spr)
	{
		sprite_order[i] = i;
		sprite_distance[i] =
					(g->p.pos.x - g->spr[i].x) * (g->p.pos.x - g->spr[i].x)
					+ (g->p.pos.y - g->spr[i].y) * (g->p.pos.y - g->spr[i].y);
	}
	descending_sort(sprite_order, sprite_distance, g->map.spr);
}

static void		calculate_spr_pos(t_game *g)
{
	g->sc.v_move_scr = (int)(V_MOVE / g->sc.transform_y);
	g->sc.sprite_height =
		abs((int)(g->scr.size.y / g->sc.transform_y)) / V_DIV;
	g->sc.draw_start_y =
		-g->sc.sprite_height / 2 + g->scr.size.y / 2 + g->sc.v_move_scr;
	if (g->sc.draw_start_y < 0)
		g->sc.draw_start_y = 0;
	g->sc.draw_end_y =
		g->sc.sprite_height / 2 + g->scr.size.y / 2 + g->sc.v_move_scr;
	if (g->sc.draw_end_y >= g->scr.size.y)
		g->sc.draw_end_y = g->scr.size.y - 1;
	g->sc.sprite_width = abs((int)(g->scr.size.y / g->sc.transform_y)) / U_DIV;
	g->sc.draw_start_x = -g->sc.sprite_width / 2 + g->sc.sprite_scr_x;
	if (g->sc.draw_start_x < 0)
		g->sc.draw_start_x = 0;
	g->sc.draw_end_x = g->sc.sprite_width / 2 + g->sc.sprite_scr_x;
	if (g->sc.draw_end_x >= g->scr.size.x)
		g->sc.draw_end_x = g->scr.size.x - 1;
}

void			calculate_spr_values(t_game *g,
											double sprite_x, double sprite_y)
{
	double	inv_det;
	double	transform_x;

	inv_det =
		1.0 / (g->p.plane.x * g->p.dir.y - g->p.dir.x * g->p.plane.y);
	transform_x =
		inv_det * (g->p.dir.y * sprite_x - g->p.dir.x * sprite_y);
	g->sc.transform_y =
		inv_det * (-g->p.plane.y * sprite_x + g->p.plane.x * sprite_y);
	g->sc.sprite_scr_x =
		(int)(g->scr.size.x / 2) * (1 + transform_x / g->sc.transform_y);
	calculate_spr_pos(g);
}

int				get_sprite_color(
			t_game *g, int *stripe, unsigned int **buffer, double *z_depth)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;

	tex_x =
		(int)(256 * (*stripe - (-g->sc.sprite_width / 2 + g->sc.sprite_scr_x))
											* 64 / g->sc.sprite_width) / 256;
	if (g->sc.transform_y > 0 && g->sc.transform_y < z_depth[*stripe]
				&& *stripe > 0 && *stripe < g->scr.size.x)
	{
		y = g->sc.draw_start_y - 1;
		while (++y < g->sc.draw_end_y)
		{
			d = (y - g->sc.v_move_scr) * 256 - g->scr.size.y * 128
									+ g->sc.sprite_height * 128;
			tex_y = ((d * 64) / g->sc.sprite_height) / 256;
			color = g->tex.i[64 * tex_y + tex_x];
			if ((color & 0x00FFFFFF) != 0)
				set_color_to_buffer(buffer, *stripe, y, color);
		}
	}
	return (0);
}
