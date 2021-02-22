/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_details.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:19:24 by tjung             #+#    #+#             */
/*   Updated: 2021/02/23 00:03:44 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_plane_v(t_game *g)
{
	if (g->p.dir_x == 0.0 && g->p.dir_y == -1.0)
		g->p.plane_x = 0.66;
	else if (g->p.dir_x == 0.0 && g->p.dir_y == 1.0)
		g->p.plane_x = -0.66;
	else if (g->p.dir_x == -1.0 && g->p.dir_y == 0.0)
		g->p.plane_y = -0.66;
	else if (g->p.dir_x == 1.0 && g->p.dir_y == 0.0)
		g->p.plane_y = 0.66;
}

int		set_sprites_config(t_game *g)
{
	int		k;
	int		i;
	int		j;

	if (!(g->spr = malloc(sizeof(t_sprite) * g->map.spr)))
		return (-1);
	k = 0;
	i = 0;
	while (i < g->map.height)
	{
		j = 0;
		while (j < g->map.width)
		{
			if (g->map.tab[i][j] == '2')
			{
				g->spr[k].x = (double)j + 0.5;
				g->spr[k].y = (double)i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	set_player_config(t_game *g)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (i < g->map.height)
	{
		j = 0;
		while (j < g->map.width)
		{
			c = g->map.tab[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				g->p.pos_x = (double)j + 0.5;
				g->p.pos_y = (double)i + 0.5;
				if (c == 'N' || c == 'S')
					g->p.dir_y = (c == 'N' ? -1.0 : 1.0);
				else if (c == 'W' || c == 'E')
					g->p.dir_x = (c == 'W' ? -1.0 : 1.0);
			}
			j++;
		}
		i++;
	}
}

int		row_len(t_game *g, char *line)
{
	int		cnt;
	int		i;

	cnt = 0;
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1')
			cnt++;
		else if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
		{
			g->flag.pnum++;
			cnt++;
		}
		else if (line[i] == '2')
		{
			g->map.spr++;
			cnt++;
		}
	}
	if (g->map.width != 0 && g->map.width != cnt)
		return (print_error(-1, "Error\nInvalid value in map\n"));
	return (cnt);
}

char	*parse_row(t_game *g, char *line, int *i)
{
	char	*row;
	int		j;

	if ((g->map.width = row_len(g, line)) == -1)
		return (NULL);
	if (!(row = malloc(sizeof(char) * (g->map.width + 1))))
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == '2'
				|| line[*i] == 'N' || line[*i] == 'S'
				|| line[*i] == 'W' || line[*i] == 'E')
			row[j++] = line[*i];
		else if (line[*i] != ' ')
		{
			free(row);
			return (NULL);
		}
		(*i)++;
	}
	row[j] = '\0';
	return (row);
}
