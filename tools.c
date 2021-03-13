/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:03:59 by tjung             #+#    #+#             */
/*   Updated: 2021/03/14 02:30:48 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_loop(t_game *g)
{
	if (g->p_move.y_move == -1)
		move_view(g, g->p.dir.x, g->p.dir.y);
	if (g->p_move.y_move == 1)
		move_view(g, -(g->p.dir.x), -(g->p.dir.y));
	if (g->p_move.x_move == -1)
		move_view(g, g->p.dir.y, -(g->p.dir.x));
	if (g->p_move.x_move == 1)
		move_view(g, -(g->p.dir.y), g->p.dir.x);
	if (g->p_move.rotate)
		rotate_view(g->p_move.rotate, g);
	start_engine(g);
	mlx_put_image_to_window(g->scr.mlx, g->scr.win, g->scr.img.ptr, 0, 0);
	return (0);
}

int		exit_hook(t_game *g)
{
	return (close_cub3d(g, 1));
}

int		close_cub3d(t_game *g, int win)
{
	if (win == 1)
		mlx_destroy_window(g->scr.mlx, g->scr.win);
	free(g->scr.mlx);
	exit(0);
	return (0);
}
