/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:45:29 by tjung             #+#    #+#             */
/*   Updated: 2021/02/23 00:03:45 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_check(t_game *g)
{
	int		i;
	int		j;

	i = 0;
	while (i < g->map.height)
	{
		j = 0;
		while (j < g->map.width)
		{
			if (g->map.tab[i][j] != '1' && i == 0)
				return (-1);
			else if (g->map.tab[i][j] != '1' && i == g->map.height - 1)
				return (-1);
			else if (g->map.tab[i][j] != '1' && j == 0)
				return (-1);
			else if (g->map.tab[i][j] != '1' && j == g->map.width - 1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int		parse_check(t_game *g)
{
	if (g->map.width <= 0 || g->map.height <= 0)
		return (print_error(-1, "Error\nResolution parsing error\n"));
	else if (g->tex.n == NULL || g->tex.s == NULL || g->tex.w == NULL
				|| g->tex.e == NULL || g->tex.i == NULL)
		return (print_error(-1, "Error\nTextures parsing error\n"));
	else if (g->tex.f == 0 || g->tex.c == 0)
		return (print_error(-1, "Error\nColors parsing error\n"));
	else if (g->flag.pnum == 0)
		return (print_error(-1, "Error\nNo player info\n"));
	else if (g->flag.pnum > 1)
		return (print_error(-1, "Error\nInvalid player info\n"));
	else if (map_check(g) == -1)
		return (print_error(-1, "Error\nMap isn't surrounded by walls\n"));
	return (0);
}
