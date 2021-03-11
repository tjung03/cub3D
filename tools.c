/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:03:59 by tjung             #+#    #+#             */
/*   Updated: 2021/03/11 19:08:08 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
