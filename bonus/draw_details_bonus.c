/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_details_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:53:08 by tjung             #+#    #+#             */
/*   Updated: 2021/03/19 03:51:16 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		set_p_dir_values(t_game *g, t_ivec *pos, int *len, int s)
{
	pos->x = g->map.minimap.x * s + (int)(s / 2);
	pos->y = g->map.minimap.y * s + (int)(s / 2);
	*len = (int)(s * 1.5);
	return (-1);
}

static void		draw_p_dir_to_buffer(t_game *g,
										char c, int s, unsigned int **buffer)
{
	t_ivec	pos;
	int		len;
	int		i;

	i = set_p_dir_values(g, &pos, &len, s);
	while (++i < len)
	{
		if (c == 'N')
			buffer[pos.y - i][pos.x] = 0xFF0000;
		else if (c == 'S')
			buffer[pos.y + i][pos.x] = 0xFF0000;
		else if (c == 'W')
			buffer[pos.y][pos.x - i] = 0xFF0000;
		else if (c == 'E')
			buffer[pos.y][pos.x + i] = 0xFF0000;
	}
}

void			draw_player_to_buffer(t_game *g, int s, unsigned int **buffer)
{
	g->map.minimap.x = (int)g->p.pos.x;
	g->map.minimap.y = (int)g->p.pos.y;
	draw_rectangle_to_buffer(g, s, buffer, 0x00FF00);
	if (g->p.plane.x >= 0.33
			&& (g->p.plane.y > -0.33 && g->p.plane.y < 0.33))
		draw_p_dir_to_buffer(g, 'N', s, buffer);
	else if (g->p.plane.x <= -0.33
			&& (g->p.plane.y > -0.33 && g->p.plane.y < 0.33))
		draw_p_dir_to_buffer(g, 'S', s, buffer);
	else if (g->p.plane.y <= -0.33
			&& (g->p.plane.x > -0.33 && g->p.plane.x < 0.33))
		draw_p_dir_to_buffer(g, 'W', s, buffer);
	else if (g->p.plane.y >= 0.33
			&& (g->p.plane.x > -0.33 && g->p.plane.x < 0.33))
		draw_p_dir_to_buffer(g, 'E', s, buffer);
}
