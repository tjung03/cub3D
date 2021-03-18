/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bar_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:41:24 by tjung             #+#    #+#             */
/*   Updated: 2021/03/18 21:52:45 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		draw_time_bar(t_game *g, int t, unsigned int **buffer)
{
	int		x;
	int		y;
	int		hor;
	int		ver;

	y = g->scr.size.y / 2 + 44;
	ver = y - 88;
	if (g->scr.size.y < 88)
	{
		y = g->scr.size.y - 1;
		ver = 0;
	}
	while (y > ver + t)
	{
		x = g->scr.size.x * 0.98;
		hor = x + g->scr.size.x / 100;
		while (x < hor)
			buffer[y][x++] = 0xFF0000;
		y--;
	}
}

int				make_time_bar(t_game *g, unsigned int **buffer, int win)
{
	int		gap;
	int		bar;

	bar = 88;
	if (g->scr.size.y < 88)
		bar = g->scr.size.y - 1;
	g->t = time(NULL);
	gap = (int)(g->t - g->st);
	if (gap >= bar)
	{
		printf("--> Time Over!\n");
		return (close_cub3d(g, win));
	}
	draw_time_bar(g, gap, buffer);
	return (0);
}
