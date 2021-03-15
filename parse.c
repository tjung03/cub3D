/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:21:55 by tjung             #+#    #+#             */
/*   Updated: 2021/03/16 04:13:01 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line_details(t_game *g, char *line, int *i)
{
	skip_space(line, i);
	if (line[*i] == 'R' && line[*i + 1] == ' ')
		g->flag.err = parse_resolution(g, line, i);
	else if (line[*i] == 'N' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		g->flag.err = parse_tex(g, &g->tex.n, line, i);
	else if (line[*i] == 'S' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		g->flag.err = parse_tex(g, &g->tex.s, line, i);
	else if (line[*i] == 'W' && line[*i + 1] == 'E' && line[*i + 2] == ' ')
		g->flag.err = parse_tex(g, &g->tex.w, line, i);
	else if (line[*i] == 'E' && line[*i + 1] == 'A' && line[*i + 2] == ' ')
		g->flag.err = parse_tex(g, &g->tex.e, line, i);
	else if (line[*i] == 'S' && line[*i + 1] == ' ')
		g->flag.err = parse_tex(g, &g->tex.i, line, i);
	else if (line[*i] == 'F' && line[*i + 1] == ' ')
		g->flag.err = parse_color(g, &g->tex.f, line, i);
	else if (line[*i] == 'C' && line[*i + 1] == ' ')
		g->flag.err = parse_color(g, &g->tex.c, line, i);
}

int		parse_line(t_game *g, char *line)
{
	int		i;

	i = 0;
	if (g->flag.m == 8 && line[i] != '\0')
		g->flag.err = parse_map(g, line, &i);
	else
		parse_line_details(g, line, &i);
	if (skip_space(line, &i) && g->flag.err == 0 && line[i] != '\0')
		return (print_error(-1, "Error\nInvalid line in file\n"));
	return (g->flag.err == -1 ? -1 : 0);
}

int		adjust_map_table(t_game *g, int *i, int *j)
{
	char	**row;
	int		x_len;

	if (!(row = malloc(sizeof(char *) * (g->map.size.y + 1))))
		return (-1);
	*i = -1;
	while (++(*i) < g->map.size.y)
	{
		if (!(row[*i] = malloc(sizeof(char) * g->map.size.x + 1)))
			return (-1);
		x_len = ft_strlen(g->map.tab[*i]);
		*j = -1;
		while (++(*j) < g->map.size.x)
		{
			if (*j < x_len)
				row[*i][*j] = g->map.tab[*i][*j];
			else
				row[*i][*j] = ' ';
		}
		row[*i][g->map.size.x] = '\0';
		free(g->map.tab[*i]);
	}
	free(g->map.tab);
	g->map.tab = row;
	return (0);
}

int		parse_cube_file(char *file, t_game *g)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (print_error(-1, "Error\nCouldn't open file(FD)\n"));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (parse_line(g, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	g->map.size.x = g->map.max_x;
	if (ret == -1)
		return (print_error(-1, "Error\nCouldn't parse file(GNL)\n"));
	if (adjust_map_table(g, &fd, &ret) == -1)
		return (print_error(-1, "Error\nInvalid Map Table\n"));
	g->map.tab[g->map.size.y] = NULL;
	set_player_config(g);
	if (set_sprites_config(g) == -1)
		return (print_error(-1, "Error\nMalloc fail(SPR_POS_INFO)\n"));
	return (parse_check(g));
}
