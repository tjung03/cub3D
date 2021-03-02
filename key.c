/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:40:09 by tjung             #+#    #+#             */
/*   Updated: 2021/03/02 23:12:20 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_view(int keycode, t_game *g)
{
	if (keycode == KEY_LEFT)
	{
		g->p.old_dir.x = g->p.dir.x;
      	g->p.dir.x = g->p.dir.x * cos(-0.06) - g->p.dir.y * sin(-0.06);
      	g->p.dir.y = g->p.old_dir.x * sin(-0.06) + g->p.dir.y * cos(-0.06);
      	g->p.old_plane.x = g->p.plane.x;
      	g->p.plane.x = g->p.plane.x * cos(-0.06) - g->p.plane.y * sin(-0.06);
      	g->p.plane.y = g->p.old_plane.x * sin(-0.06) + g->p.plane.y * cos(-0.06);
	}
	if (keycode == KEY_RIGHT)
	{
		g->p.old_dir.x = g->p.dir.x;
		g->p.dir.x = g->p.dir.x * cos(0.06) - g->p.dir.y * sin(0.06);
		g->p.dir.y = g->p.old_dir.x * sin(0.06) + g->p.dir.y * cos(0.06);
		g->p.old_plane.x = g->p.plane.x;
		g->p.plane.x = g->p.plane.x * cos(0.06) - g->p.plane.y * sin(0.06);
		g->p.plane.y = g->p.old_plane.x * sin(0.06) + g->p.plane.y * cos(0.06);
	}
}

void	move_view(t_game *g, double delta_x, double delta_y)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = g->p.pos.x + delta_x * 0.1;
	tmp_y = g->p.pos.y + delta_y * 0.1;
	if (g->map.tab[(int)g->p.pos.y][(int)g->p.pos.x] != '1')
	{
		if (g->map.tab[(int)tmp_y][(int)tmp_x] != '1')
		{
			g->p.pos.x = tmp_x;
			g->p.pos.y = tmp_y;
		}
	}
}

int		key_press(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		close_cub3d(g, 1);
	if (keycode == KEY_W)
		move_view(g, g->p.dir.x, g->p.dir.y);
	if (keycode == KEY_A)
		move_view(g, g->p.dir.y, -(g->p.dir.x));
	if (keycode == KEY_S)
		move_view(g, -(g->p.dir.x), -(g->p.dir.y));
	if (keycode == KEY_D)
		move_view(g, -(g->p.dir.y), g->p.dir.x);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_view(keycode, g);
	start_engine(g);
	mlx_put_image_to_window(g->scr.mlx, g->scr.win, g->img.ptr, 0, 0);
	return (0);
}
