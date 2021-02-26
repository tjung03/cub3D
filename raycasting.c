/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:47:30 by tjung             #+#    #+#             */
/*   Updated: 2021/02/26 23:37:13 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_zero_rcv(t_game *g)
{
	g->rc.camera_x = 0.0;
	g->rc.ray_dir.x = 0.0;
	g->rc.ray_dir.y = 0.0;
	g->rc.delta_dist.x = 0.0;
	g->rc.delta_dist.y = 0.0;
	g->rc.side_dist.x = 0.0;
	g->rc.side_dist.y = 0.0;
	g->rc.perp_wall_dist = 0.0;
	g->rc.map.x = 0;
	g->rc.map.y = 0;
	g->rc.step.x = 0;
	g->rc.step.y = 0;
	g->rc.hit = 0;
	g->rc.side = 0;
}

void	set_rcv(t_game *g, int x)
{
	g->rc.camera_x = (2 * x / (double)g->scr.size.x) - 1.0;
	g->rc.ray_dir.x = g->p.dir.x + (g->p.plane.x * g->rc.camera_x);
	g->rc.ray_dir.y = g->p.dir.y + (g->p.plane.y * g->rc.camera_x);
	g->rc.map.x = (int)g->p.pos.x;
	g->rc.map.y = (int)g->p.pos.y;
	g->rc.delta_dist.x = fabs(1.0 / g->rc.ray_dir.x);
	g->rc.delta_dist.y = fabs(1.0 / g->rc.ray_dir.y);
	g->rc.hit = 0;
}

void	calculate_ray_dist(t_game *g)
{
	if (g->rc.ray_dir.x < 0)
	{
		g->rc.step.x = -1;
		g->rc.side_dist.x = (g->p.pos.x - g->rc.map.x) * g->rc.delta_dist.x;
	}
	else
	{
		g->rc.step.x = 1;
		g->rc.side_dist.x =
						(g->rc.map.x + 1.0 - g->p.pos.x) * g->rc.delta_dist.x;
	}
	if (g->rc.ray_dir.y < 0)
	{
		g->rc.step.y = -1;
		g->rc.side_dist.y = (g->p.pos.y - g->rc.map.y) * g->rc.delta_dist.y;
	}
	else
	{
		g->rc.step.y = 1;
		g->rc.side_dist.y =
						(g->rc.map.y + 1.0 - g->p.pos.y) * g->rc.delta_dist.y;
	}
}

void	perform_dda(t_game *g)
{
	while (g->rc.hit == 0)
	{
		if (g->rc.side_dist.x < g->rc.side_dist.y)
		{
			g->rc.side_dist.x += g->rc.delta_dist.x;
			g->rc.map.x += g->rc.step.x;
			g->rc.side = 0;
		}
		else
		{
			g->rc.side_dist.y += g->rc.delta_dist.y;
			g->rc.map.y += g->rc.step.y;
			g->rc.side = 1;
		}
		if (g->map.tab[g->rc.map.y][g->rc.map.x] > '0')
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
					((double)g->rc.map.x - g->p.pos.x +
					((1.0 - (double)g->rc.step.x) / 2.0)) /
					g->rc.ray_dir.x;
	else
		g->rc.perp_wall_dist =
					((double)g->rc.map.y - g->p.pos.y +
					((1.0 - (double)g->rc.step.y) / 2.0)) /
					g->rc.ray_dir.y;
	*line_h = (int)(g->scr.size.y / g->rc.perp_wall_dist);
}
