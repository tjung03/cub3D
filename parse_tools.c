/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:55:46 by tjung             #+#    #+#             */
/*   Updated: 2021/02/23 01:13:11 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_map(t_game *g, char *line, int *i)
{
	char	**tmp;
	int		j;

	g->flag.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (g->map.height + 2))))
		return (print_error(-1, "Error\nMalloc fail(Map table)\n"));
	j = -1;
	while (++j < g->map.height)
		tmp[j] = g->map.tab[j];
	if ((tmp[g->map.height] = parse_row(g, line, i)) == NULL)
	{
		free(tmp);
		return (print_error(-1, "Error\nInvalid map config\n"));
	}
	tmp[g->map.height + 1] = NULL;
	if (g->map.height > 0)
		free(g->map.tab);
	g->map.tab = tmp;
	g->map.height++;
	return (0);
}

int		parse_resolution(t_game *g, char *line, int *i)
{
	int		w;
	int		h;

	(*i)++;
	mlx_get_screen_size(g->scr.mlx, &w, &h);
	g->scr.width = ft_atoi(line, i);
	g->scr.height = ft_atoi(line, i);
	if (g->scr.width > w)
		g->scr.width = w;
	if (g->scr.height > h)
		g->scr.height = h;
	skip_space(line, i);
	if (g->scr.width <= 0 || g->scr.height <= 0 || line[*i] != '\0')
		return (print_error(-1, "Error\nInvalid resolution\n"));
	return (0);
}

int		parse_xpm(t_game *g, unsigned int **tex, char *fname)
{
	int		fd;
	void	*img;
	int		tex_info[5];

	if (check_file_name(fname, ".xpm") == -1)
		return (print_error(-1, "Error\nInvalid texture path\n"));
	if ((fd = open(fname, O_RDONLY)) == -1)
		return (print_error(-1, "Error\nInvalid texture image\n"));
	close(fd);
	img = mlx_xpm_file_to_image(g->scr.mlx, fname, &tex_info[0], &tex_info[1]);
	if (img == NULL || tex_info[0] != 64 || tex_info[1] != 64)
		return (print_error(-1, "Error\nInvalid tex-image config\n"));
	*tex = (unsigned int *)mlx_get_data_addr(
								img, &tex_info[2], &tex_info[3], &tex_info[4]);
	free(img);
	return (0);
}

int		parse_tex(t_game *g, unsigned int **tex, char *line, int *i)
{
	char	*fname;
	int		j;

	(*i) += 2;
	skip_space(line, i);
	j = (*i);
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(fname = malloc(sizeof(char) * (*i - j + 1))))
		return (print_error(-1, "Error\nMalloc fail(Texture path)\n"));
	(*i) = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		fname[j++] = line[(*i)++];
	fname[j] = '\0';
	j = parse_xpm(g, tex, fname);
	free(fname);
	if (j == -1)
		return (-1);
	return (0);
}

int		parse_color(unsigned int *color, char *line, int *i)
{
	int		r;
	int		g;
	int		b;

	(*i)++;
	r = ft_atoi(line, i);
	(*i)++;
	g = ft_atoi(line, i);
	(*i)++;
	b = ft_atoi(line, i);
	skip_space(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (print_error(-1, "Error\nInvalid floor/ceiling color\n"));
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}
