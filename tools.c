/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:03:59 by tjung             #+#    #+#             */
/*   Updated: 2021/02/18 19:49:01 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_cub3d(t_game *g, int win)
{
	int		i;

	i = -1;
	while (++i < g->map.mHeight)
	{
		if (g->map.tab[i])
			free(g->map.tab[i]);
	}
	if (g->map.tab)
		free(g->map.tab);
	if (g->tex.e)
		free(g->tex.e);
	if (g->tex.w)
		free(g->tex.w);
	if (g->tex.s)
		free(g->tex.s);
	if (g->tex.n)
		free(g->tex.n);
	if (g->tex.i)
		free(g->tex.i);
	if (win == 1)
		mlx_destroy_window(g->scr.mlx, g->scr.win);
	free(g->scr.mlx);
	exit(0);
	return (0);
}