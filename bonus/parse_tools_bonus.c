/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:55:46 by tjung             #+#    #+#             */
/*   Updated: 2021/03/18 22:44:16 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			parse_map(t_game *g, char *line, int *i)
{
	char	**tmp;
	int		j;
	int		valid;

	if (!(valid = valid_line(line, 0)))
		return (0);
	else if (valid == -1)
		return (print_error(-1, "Error\nInvalid line in Map Value\n"));
	if (!(tmp = malloc(sizeof(char *) * (g->map.size.y + 2))))
		return (print_error(-1, "Error\nMalloc fail(Map table)\n"));
	j = -1;
	while (++j < g->map.size.y)
		tmp[j] = g->map.tab[j];
	if ((tmp[g->map.size.y] = parse_row(g, line, i)) == NULL)
	{
		free(tmp);
		return (print_error(-1, "Error\nInvalid map config\n"));
	}
	tmp[g->map.size.y + 1] = NULL;
	if (g->map.size.y > 0)
		free(g->map.tab);
	g->map.tab = tmp;
	g->map.size.y++;
	return (0);
}

int			parse_resolution(t_game *g, char *line, int *i)
{
	int		w;
	int		h;

	(*i)++;
	mlx_get_screen_size(g->scr.mlx, &w, &h);
	g->scr.size.x = ft_atoi(line, i);
	g->scr.size.y = ft_atoi(line, i);
	if (g->scr.size.x > w)
		g->scr.size.x = w;
	if (g->scr.size.y > h)
		g->scr.size.y = h;
	skip_space(line, i);
	if (g->scr.size.x <= 0 || g->scr.size.y <= 0 || line[*i] != '\0')
		return (print_error(-1, "Error\nInvalid resolution\n"));
	g->flag.m++;
	return (0);
}

static int	parse_xpm(t_game *g, unsigned int **tex, char *fname)
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
		return (print_error(-1, "Error\nInvalid tex-image config(64x64)\n"));
	*tex = (unsigned int *)mlx_get_data_addr(
								img, &tex_info[2], &tex_info[3], &tex_info[4]);
	free(img);
	return (0);
}

int			parse_tex(t_game *g, unsigned int **tex, char *line, int *i)
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
	g->flag.m++;
	return (0);
}

int			parse_color(t_game *g, unsigned int *color, char *line, int *i)
{
	int		red;
	int		green;
	int		blue;

	(*i)++;
	red = ft_atoi(line, i);
	(*i)++;
	green = ft_atoi(line, i);
	(*i)++;
	blue = ft_atoi(line, i);
	skip_space(line, i);
	if (line[*i] != '\0' || red > 255 || green > 255 || blue > 255)
		return (print_error(-1, "Error\nInvalid floor/ceiling color\n"));
	*color = red * 256 * 256 + green * 256 + blue;
	g->flag.m++;
	return (0);
}
