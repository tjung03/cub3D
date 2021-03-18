/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:47:36 by tjung             #+#    #+#             */
/*   Updated: 2021/03/19 04:02:00 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		run_mlx_hook(t_game *g)
{
	mlx_hook(g->scr.win, X_EVENT_KEY_PRESS, 0, &key_press, g);
	mlx_hook(g->scr.win, X_EVENT_KEY_RELEASE, 0, &key_release, g);
	mlx_hook(g->scr.win, X_EVENT_MOTION_NOTIFY, 0, &key_mouse, g);
	mlx_hook(g->scr.win, X_EVENT_KEY_EXIT, 0, &exit_hook, g);
	mlx_loop_hook(g->scr.mlx, &main_loop, g);
}

int				start_cub3d(char *file, int bmp)
{
	t_game		g;

	init_zero(&g);
	init_zero_rcv(&g);
	g.scr.mlx = mlx_init();
	if (parse_cube_file(file, &g) == -1)
		return (close_cub3d(&g, 0));
	if (malloc_buffer(&g) == -1)
		return (close_cub3d(&g, 0));
	g.t = time(NULL);
	g.st = g.t;
	if (bmp == 1)
		return (make_bitmap(&g, g.buffer));
	g.scr.win = mlx_new_window(g.scr.mlx, g.scr.size.x, g.scr.size.y,
																"cub3D_bonus");
	g.scr.img.ptr = mlx_new_image(g.scr.mlx, g.scr.size.x, g.scr.size.y);
	g.scr.img.adr = mlx_get_data_addr(
		g.scr.img.ptr, &g.scr.img.bpp, &g.scr.img.sl, &g.scr.img.endian);
	run_bgm();
	run_mlx_hook(&g);
	mlx_loop(g.scr.mlx);
	return (0);
}
