/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:47:36 by tjung             #+#    #+#             */
/*   Updated: 2021/03/16 19:23:23 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		init_zero_scr(t_screen *scr)
{
	scr->mlx = NULL;
	scr->win = NULL;
	scr->size.x = 0;
	scr->size.y = 0;
	scr->img.ptr = NULL;
	scr->img.adr = NULL;
	scr->img.bpp = 0;
	scr->img.sl = 0;
	scr->img.endian = 0;
}

static void		init_zero_tex(t_tex *tex)
{
	tex->tex_pos = 0.0;
	tex->tex_x = 0;
	tex->tex_y = 0;
	tex->e = NULL;
	tex->w = NULL;
	tex->s = NULL;
	tex->n = NULL;
	tex->i = NULL;
	tex->c = 0x0;
	tex->f = 0x0;
}

static void		init_zero_map(t_map *map)
{
	map->tab = NULL;
	map->size.x = 0;
	map->size.y = 0;
	map->spr = 0;
	map->max_x = 0;
}

static void		init_zero(t_game *g)
{
	init_zero_scr(&g->scr);
	init_zero_tex(&g->tex);
	init_zero_map(&g->map);
	g->flag.err = 0;
	g->flag.m = 0;
	g->flag.pnum = 0;
	g->p_move.y_move = 0;
	g->p_move.x_move = 0;
	g->p_move.rotate = 0;
	g->p.pos.x = 0.0;
	g->p.pos.y = 0.0;
	g->p.dir.x = 0.0;
	g->p.dir.y = 0.0;
	g->p.o_dir.x = 0.0;
	g->p.o_dir.y = 0.0;
	g->p.plane.x = 0.0;
	g->p.plane.y = 0.0;
	g->p.o_plane.x = 0.0;
	g->p.o_plane.y = 0.0;
	g->spr = NULL;
	g->buffer = NULL;
}

int				start_cub3d(char *file, int bmp)
{
	t_game			g;

	init_zero(&g);
	init_zero_rcv(&g);
	g.scr.mlx = mlx_init();
	if (parse_cube_file(file, &g) == -1)
		return (close_cub3d(&g, 0));
	if (malloc_buffer(&g) == -1)
		return (close_cub3d(&g, 0));
	if (bmp == 1)
		return (make_bitmap(&g, g.buffer));
	g.scr.win = mlx_new_window(g.scr.mlx, g.scr.size.x, g.scr.size.y, "cub3d");
	g.scr.img.ptr = mlx_new_image(g.scr.mlx, g.scr.size.x, g.scr.size.y);
	g.scr.img.adr = mlx_get_data_addr(
		g.scr.img.ptr, &g.scr.img.bpp, &g.scr.img.sl, &g.scr.img.endian);
	mlx_put_image_to_window(g.scr.mlx, g.scr.win, g.scr.img.ptr, 0, 0);
	mlx_hook(g.scr.win, X_EVENT_KEY_PRESS, 0, &key_press, &g);
	mlx_hook(g.scr.win, X_EVENT_KEY_RELEASE, 0, &key_release, &g);
	mlx_hook(g.scr.win, X_EVENT_KEY_EXIT, 0, &exit_hook, &g);
	mlx_loop_hook(g.scr.mlx, &main_loop, &g);
	mlx_loop(g.scr.mlx);
	return (0);
}
