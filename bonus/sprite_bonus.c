/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:30:01 by tjung             #+#    #+#             */
/*   Updated: 2021/03/18 22:33:01 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		init_zero_scv(t_game *g)
{
	g->sc.transform_y = 0.0;
	g->sc.sprite.x = 0.0;
	g->sc.sprite.y = 0.0;
	g->sc.sprite.type = '\0';
	g->sc.sprite_scr_x = 0;
	g->sc.v_move_scr = 0;
	g->sc.sprite_height = 0;
	g->sc.draw_start_y = 0;
	g->sc.draw_end_y = 0;
	g->sc.sprite_width = 0;
	g->sc.draw_start_x = 0;
	g->sc.draw_end_x = 0;
}

static void		get_sprites(t_game *g,
			int *sprite_order, unsigned int **buffer, double *z_depth)
{
	int		stripe;
	int		i;

	i = -1;
	while (++i < g->map.spr)
	{
		g->sc.sprite.x = g->spr[sprite_order[i]].x - g->p.pos.x;
		g->sc.sprite.y = g->spr[sprite_order[i]].y - g->p.pos.y;
		g->sc.sprite.type = g->spr[sprite_order[i]].type;
		calculate_spr_values(g, g->sc.sprite.x, g->sc.sprite.y);
		stripe = g->sc.draw_start_x - 1;
		while (++stripe < g->sc.draw_end_x)
			get_sprite_color(g, &stripe, buffer, z_depth);
	}
}

int				print_sprite_to_buffer(
					t_game *g, unsigned int **buffer, double *z_depth)
{
	double	sprite_distance[g->map.spr];
	int		sprite_order[g->map.spr];

	init_zero_scv(g);
	sort_sprites(g, sprite_order, sprite_distance);
	get_sprites(g, sprite_order, buffer, z_depth);
	return (0);
}
