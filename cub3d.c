/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:47:36 by tjung             #+#    #+#             */
/*   Updated: 2021/03/02 21:40:44 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_zero_scr(t_screen *scr)
{
	scr->mlx = NULL;
	scr->win = NULL;
	scr->size.x = 0;
	scr->size.y = 0;
}

void	init_zero_tex(t_tex *tex)
{
	tex->e = NULL;
	tex->w = NULL;
	tex->s = NULL;
	tex->n = NULL;
	tex->i = NULL;
	tex->c = 0x0;
	tex->f = 0x0;
}

void	init_zero_map(t_map *map)
{
	map->tab = NULL;
	map->size.x = 0;
	map->size.y = 0;
	map->spr = 0;
}

void	init_zero(t_game *g)
{
	init_zero_scr(&g->scr);
	init_zero_tex(&g->tex);
	init_zero_map(&g->map);
	g->img.ptr = NULL;
	g->img.adr = NULL;
	g->img.bpp = 0;
	g->img.size_line = 0;
	g->img.endian = 0;
	g->flag.err = 0;
	g->flag.m = 0;
	g->flag.pnum = 0;
	g->p.pos.x = 0.0;
	g->p.pos.y = 0.0;
	g->p.dir.x = 0.0;
	g->p.dir.y = 0.0;
	g->p.old_dir.x = 0.0;
	g->p.old_dir.y = 0.0;
	g->p.plane.x = 0.0;
	g->p.plane.y = 0.0;
	g->p.old_plane.x = 0.0;
	g->p.old_plane.y = 0.0;
	g->spr = NULL;
}

int		start_cub3d(char *file, int bmp)
{
	t_game	g;

	init_zero(&g);
	init_zero_rcv(&g);
	g.scr.mlx = mlx_init();
	if (parse_cube_file(file, &g) == -1)
		return (close_cub3d(&g, 0));
	if (bmp == 1)
		return (make_bitmap(&g));
	g.scr.win = mlx_new_window(g.scr.mlx, g.scr.size.x, g.scr.size.y, "cub3d");
	g.img.ptr = mlx_new_image(g.scr.mlx, g.scr.size.x, g.scr.size.y);
	g.img.adr = mlx_get_data_addr(
					g.img.ptr, &g.img.bpp, &g.img.size_line, &g.img.endian);
	if (start_engine(&g) == -1)
		return (close_cub3d(&g, 1));
	mlx_hook(g.scr.win, X_EVENT_KEY_PRESS, 0, &key_press, &g);
	mlx_put_image_to_window(g.scr.mlx, g.scr.win, g.img.ptr, 0, 0);
	mlx_loop(g.scr.mlx);
	return (0);
}
