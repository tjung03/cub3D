/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:46:24 by tjung             #+#    #+#             */
/*   Updated: 2021/02/24 23:23:20 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		start_engine(t_game *g)
{
	int		line_h;
	int		x;

	set_plane_v(g);
	line_h = 0;
	x = -1;
	while (++x < g->scr.width)
	{
		get_line_h(g, x, &line_h);
		//draw_vertical_l(g, line_h, x, g->tex.c);
	}
	return (0);
}
