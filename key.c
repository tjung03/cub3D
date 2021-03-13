/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:40:09 by tjung             #+#    #+#             */
/*   Updated: 2021/03/14 05:32:40 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_view(int keycode, t_game *g)
{
	if (keycode == -1)
	{
		g->p.o_dir.x = g->p.dir.x;
		g->p.dir.x = g->p.dir.x * cos(-0.06) - g->p.dir.y * sin(-0.06);
		g->p.dir.y = g->p.o_dir.x * sin(-0.06) + g->p.dir.y * cos(-0.06);
		g->p.o_plane.x = g->p.plane.x;
		g->p.plane.x = g->p.plane.x * cos(-0.06) - g->p.plane.y * sin(-0.06);
		g->p.plane.y = g->p.o_plane.x * sin(-0.06) + g->p.plane.y * cos(-0.06);
	}
	if (keycode == 1)
	{
		g->p.o_dir.x = g->p.dir.x;
		g->p.dir.x = g->p.dir.x * cos(0.06) - g->p.dir.y * sin(0.06);
		g->p.dir.y = g->p.o_dir.x * sin(0.06) + g->p.dir.y * cos(0.06);
		g->p.o_plane.x = g->p.plane.x;
		g->p.plane.x = g->p.plane.x * cos(0.06) - g->p.plane.y * sin(0.06);
		g->p.plane.y = g->p.o_plane.x * sin(0.06) + g->p.plane.y * cos(0.06);
	}
}

void	move_view(t_game *g, double delta_x, double delta_y)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = g->p.pos.x + delta_x * 0.3;
	tmp_y = g->p.pos.y + delta_y * 0.3;
	if (g->map.tab[(int)g->p.pos.y][(int)g->p.pos.x] != '1')
	{
		if (g->map.tab[(int)tmp_y][(int)tmp_x] != '1'
				&& g->map.tab[(int)tmp_y][(int)tmp_x] != '2')
		{
			g->p.pos.x += delta_x * 0.1;
			g->p.pos.y += delta_y * 0.1;
		}
	}
}

int		key_press(int keycode, t_game *g)
{
	if (keycode == KEY_W)
		g->p_move.y_move = -1;
	else if (keycode == KEY_S)
		g->p_move.y_move = 1;
	if (keycode == KEY_A)
		g->p_move.x_move = -1;
	else if (keycode == KEY_D)
		g->p_move.x_move = 1;
	if (keycode == KEY_LEFT)
		g->p_move.rotate = -1;
	else if (keycode == KEY_RIGHT)
		g->p_move.rotate = 1;
	return (0);
}

int		key_release(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		close_cub3d(g, 1);
	if (keycode == KEY_W)
		g->p_move.y_move = 0;
	if (keycode == KEY_A)
		g->p_move.x_move = 0;
	if (keycode == KEY_S)
		g->p_move.y_move = 0;
	if (keycode == KEY_D)
		g->p_move.x_move = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		g->p_move.rotate = 0;
	return (0);
}
