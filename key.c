/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:40:09 by tjung             #+#    #+#             */
/*   Updated: 2021/02/26 23:41:13 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		close_cub3d(g, 1);
	if (keycode == KEY_W)
		g->p.pos.y -= 0.1;
	if (keycode == KEY_A)
		g->p.pos.x -= 0.1;
	if (keycode == KEY_S)
		g->p.pos.y += 0.1;
	if (keycode == KEY_D)
		g->p.pos.x += 0.1;
	printf("%lf, %lf\n", g->p.pos.x, g->p.pos.y);
	draw_map(g);
	draw_player(g);
	mlx_put_image_to_window(g->scr.mlx, g->scr.win, g->img.ptr, 0, 0);
	return (0);
}
