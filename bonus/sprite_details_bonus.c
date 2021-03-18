/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_details_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:11:57 by tjung             #+#    #+#             */
/*   Updated: 2021/03/19 04:11:44 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void		get_color_spr_tex(t_game *g, int x, int y, unsigned int *color)
{
	if (g->sc.sprite.type == '2')
		*color = g->tex.i[64 * y + x];
	else if (g->sc.sprite.type == '3')
		*color = g->tex.ii[64 * y + x];
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
			get_color_spr_tex(g, tex_x, tex_y, &color);
			if ((color & 0x00FFFFFF) != 0)
				set_color_to_buffer(buffer, *stripe, y, color);
		}
	}
	return (0);
}
