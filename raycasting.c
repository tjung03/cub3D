/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:47:30 by tjung             #+#    #+#             */
/*   Updated: 2021/02/23 07:03:53 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_zero_rcv(t_game *g)
{
	g->rc.camera_x = 0.0;
	g->rc.ray_dir_x = 0.0;
	g->rc.ray_dir_y = 0.0;
	g->rc.delta_dist_x = 0.0;
	g->rc.delta_dist_y = 0.0;
	g->rc.side_dist_x = 0.0;
	g->rc.side_dist_y = 0.0;
	g->rc.perp_wall_dist = 0.0;
	g->rc.map_x = 0;
	g->rc.map_y = 0;
	g->rc.step_x = 0;
	g->rc.step_y = 0;
	g->rc.hit = 0;
	g->rc.side = 0;
}

void	set_rcv(t_game *g, int x)
{
	g->rc.camera_x = (2 * x / (double)g->scr.width) - 1.0;
	g->rc.ray_dir_x = g->p.dir_x + (g->p.plane_x * g->rc.camera_x);
	g->rc.ray_dir_y = g->p.dir_y + (g->p.plane_y * g->rc.camera_x);
	g->rc.map_x = (int)g->p.pos_x;
	g->rc.map_y = (int)g->p.pos_y;
	g->rc.delta_dist_x = fabs(1.0 / g->rc.ray_dir_x);
	g->rc.delta_dist_y = fabs(1.0 / g->rc.ray_dir_y);
}

void	calculate_ray_dist(t_game *g)
{
	if (g->rc.ray_dir_x < 0)
	{
		g->rc.step_x = -1;
		g->rc.side_dist_x = (g->p.pos_x - g->rc.map_x) * g->rc.delta_dist_x;
	}
	else
	{
		g->rc.step_x = 1;
		g->rc.side_dist_x =
						(g->rc.map_x + 1.0 - g->p.pos_x) * g->rc.delta_dist_x;
	}
	if (g->rc.ray_dir_y < 0)
	{
		g->rc.step_y = -1;
		g->rc.side_dist_y = (g->p.pos_y - g->rc.map_y) * g->rc.delta_dist_y;
	}
	else
	{
		g->rc.step_y = 1;
		g->rc.side_dist_y =
						(g->rc.map_y + 1.0 - g->p.pos_y) * g->rc.delta_dist_y;
	}
}

void	perform_dda(t_game *g)
{
	while (g->rc.hit == 0)
	{
		if (g->rc.side_dist_x < g->rc.side_dist_y)
		{
			g->rc.side_dist_x += g->rc.delta_dist_x;
			g->rc.map_x += g->rc.step_x;
			g->rc.side = 0;
		}
		else
		{
			g->rc.side_dist_y += g->rc.delta_dist_y;
			g->rc.map_y += g->rc.step_y;
			g->rc.side = 1;
		}
		if (g->map.tab[g->rc.map_y][g->rc.map_x] > '0')
			g->rc.hit = 1;
	}
}

void	get_line_h(t_game *g, int x, int *line_h)
{
	set_rcv(g, x);
	calculate_ray_dist(g);
	perform_dda(g);
	if (g->rc.side == 0)
		g->rc.perp_wall_dist =
					((double)g->rc.map_x - g->p.pos_x +
					(1.0 - (double)g->rc.step_x) / 2.0) /
					g->rc.ray_dir_x;
	else
		g->rc.perp_wall_dist =
					((double)g->rc.map_y - g->p.pos_y +
					(1.0 - (double)g->rc.step_y) / 2.0) /
					g->rc.ray_dir_y;
	*line_h = (int)(g->scr.height / g->rc.perp_wall_dist);
}
