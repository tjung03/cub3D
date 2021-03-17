/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_details_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:19:24 by tjung             #+#    #+#             */
/*   Updated: 2021/03/17 17:45:35 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		set_plane_values(t_game *g)
{
	if (g->p.dir.x == 0.0 && g->p.dir.y == -1.0)
		g->p.plane.x = 0.66;
	else if (g->p.dir.x == 0.0 && g->p.dir.y == 1.0)
		g->p.plane.x = -0.66;
	else if (g->p.dir.x == -1.0 && g->p.dir.y == 0.0)
		g->p.plane.y = -0.66;
	else if (g->p.dir.x == 1.0 && g->p.dir.y == 0.0)
		g->p.plane.y = 0.66;
}

int			set_sprites_config(t_game *g)
{
	int		k;
	int		i;
	int		j;

	if (!(g->spr = malloc(sizeof(t_fvec) * g->map.spr)))
		return (-1);
	k = 0;
	i = 0;
	while (i < g->map.size.y)
	{
		j = 0;
		while (j < g->map.size.x)
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

void		set_player_config(t_game *g)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (i < g->map.size.y)
	{
		j = 0;
		while (j < g->map.size.x)
		{
			c = g->map.tab[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				g->p.pos.x = (double)j + 0.5;
				g->p.pos.y = (double)i + 0.5;
				if (c == 'N' || c == 'S')
					g->p.dir.y = (c == 'N' ? -1.0 : 1.0);
				else if (c == 'W' || c == 'E')
					g->p.dir.x = (c == 'W' ? -1.0 : 1.0);
			}
			j++;
		}
		i++;
	}
}

static int	row_len(t_game *g, char *line)
{
	int		cnt;
	int		valid;
	int		i;

	cnt = 0;
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2'
				&& line[i] != 'N' && line[i] != 'S'
				&& line[i] != 'W' && line[i] != 'E'
				&& line[i] != ' ')
			return (print_error(-1, "Error\nInvalid value in MAP\n"));
		if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
			g->flag.pnum++;
		if (line[i] == '2')
			g->map.spr++;
		cnt++;
		if (!(valid = valid_line(line, i + 1)))
			break ;
		else if (valid == -1)
			return (print_error(-1, "Error\nInvalid value in MAP\n"));
	}
	return (cnt);
}

char		*parse_row(t_game *g, char *line, int *i)
{
	char	*row;

	if ((g->map.size.x = row_len(g, line)) == -1)
		return (NULL);
	if (g->map.max_x < g->map.size.x)
		g->map.max_x = g->map.size.x;
	if (!(row = malloc(sizeof(char) * (g->map.size.x + 1))))
		return (NULL);
	while (*i < g->map.size.x)
	{
		row[*i] = line[*i];
		(*i)++;
	}
	row[g->map.size.x] = '\0';
	return (row);
}
