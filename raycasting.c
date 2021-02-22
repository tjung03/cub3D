/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:47:20 by tjung             #+#    #+#             */
/*   Updated: 2021/02/22 14:48:19 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_plane(t_game *g)
{
	if (g->p.dirX == 0.0 && g->p.dirY == -1.0)
		g->p.planeX = 0.66;
	else if (g->p.dirX == 0.0 && g->p.dirY == 1.0)
		g->p.planeX = -0.66;
	else if (g->p.dirX == -1.0 && g->p.dirY == 0.0)
		g->p.planeY = -0.66;
	else if (g->p.dirX == 1.0 && g->p.dirY == 0.0)
		g->p.planeY = 0.66;
}

int		start_engine(t_game *g)
{
	set_plane(g);
	return (0);
}