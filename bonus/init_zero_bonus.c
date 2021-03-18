/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zero_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:52:22 by tjung             #+#    #+#             */
/*   Updated: 2021/03/19 00:30:20 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	tex->ii = NULL;
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

void			init_zero(t_game *g)
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
	g->t = 0;
	g->st = 0;
	g->m = 0;
}
