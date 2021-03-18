/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:45:29 by tjung             #+#    #+#             */
/*   Updated: 2021/03/18 22:06:17 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	map_ver_check_details(t_game *g, char **tmp, int *i, int *j)
{
	int		y_max;

	y_max = g->map.size.y;
	if (tmp[0][*j] != '1' && tmp[0][*j] != ' ')
		return (-1);
	else if (tmp[y_max - 1][*j] != '1' && tmp[y_max - 1][*j] != ' ')
		return (-1);
	else if (tmp[*i][*j] != '1' && tmp[*i][*j] != ' ')
	{
		if (tmp[*i - 1][*j] == ' ')
			return (-1);
		if (*i < y_max - 1)
		{
			if (tmp[*i + 1][*j] == ' ')
				return (-1);
		}
	}
	return (0);
}

static int	map_ver_check(t_game *g)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = g->map.tab;
	i = 0;
	while (++i < g->map.size.y)
	{
		j = -1;
		while (++j < g->map.size.x)
		{
			if (map_ver_check_details(g, tmp, &i, &j) == -1)
				return (0);
		}
	}
	return (0);
}

static int	map_hor_check(t_game *g)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < g->map.size.y)
	{
		tmp = g->map.tab[i];
		if (tmp[0] != '1' && tmp[0] != ' ')
			return (-1);
		j = 0;
		while (++j < g->map.size.x)
		{
			if (tmp[j] != '1' && tmp[j] != ' ')
			{
				if (tmp[j + 1] == '\0')
					return (-1);
				if (tmp[j + 1] == ' ' || tmp[j - 1] == ' ')
					return (-1);
			}
		}
	}
	return (0);
}

static int	map_check(t_game *g)
{
	if (map_hor_check(g) == -1)
		return (-1);
	if (map_ver_check(g) == -1)
		return (-1);
	return (0);
}

int			parse_check(t_game *g)
{
	if (g->map.size.x <= 0 || g->map.size.y <= 0)
		return (print_error(-1, "Error\nResolution parsing error\n"));
	else if (g->tex.n == NULL || g->tex.s == NULL || g->tex.w == NULL
				|| g->tex.e == NULL || g->tex.i == NULL || g->tex.ii == NULL)
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
