/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:05:38 by tjung             #+#    #+#             */
/*   Updated: 2021/02/24 23:22:42 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

typedef struct	s_screen {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}				t_screen;

typedef struct	s_img {
	void	*ptr;
	char	*adr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_flag {
	int		err;
	int		m;
	int		pnum;
}				t_flag;

typedef struct	s_tex {
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*s;
	unsigned int	*n;
	unsigned int	*i;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct	s_map {
	char	**tab;
	int		width;
	int		height;
	int		spr;
}				t_map;

typedef struct	s_sprite {
	double	x;
	double	y;
}				t_sprite;

typedef struct	s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct	s_raycasting {
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}				t_raycasting;

typedef struct	s_game {
	t_screen		scr;
	t_img			img;
	t_flag			flag;
	t_tex			tex;
	t_map			map;
	t_player		p;
	t_sprite		*spr;
	t_raycasting	rc;
}				t_game;

/*
**				main.c
*/

int				print_error(int e, char *msg);
int				check_save_opt(char *s);
int				check_file_name(char *s, char *extension);

/*
**				cub3d.c
*/

int				start_cub3d(char *file, int bmp);
void			init_zero_scr(t_screen *scr);
void			init_zero_tex(t_tex *tex);
void			init_zero_map(t_map *map);
void			init_zero(t_game *g);

/*
**				tools.c
*/

int				close_cub3d(t_game *g, int win);

/*
**				parse.c
*/

int				parse_cube_file(char *file, t_game *g);

/*
**				parse_tools.c
*/

int				parse_map(t_game *g, char *line, int *i);
int				parse_resolution(t_game *g, char *line, int *i);
int				parse_tex(t_game *g, unsigned int **tex, char *line, int *i);
int				parse_xpm(t_game *g, unsigned int **tex, char *fname);
int				parse_color(unsigned int *color, char *line, int *i);

/*
**				parse_tools_details.c
*/

char			*parse_row(t_game *g, char *line, int *i);
int				row_len(t_game *g, char *line);
void			set_player_config(t_game *g);
int				set_sprites_config(t_game *g);
void			set_plane_v(t_game *g);

/*
**				parse_check.c
*/

int				parse_check(t_game *g);
int				map_check(t_game *g);

/*
**				bitmap.c
*/

int				make_bitmap(t_game *g);

/*
**				engine.c
*/

int				start_engine(t_game *g);

/*
**				raycasting.c
*/

void			get_line_h(t_game *g, int x, int *line_h);
void			init_zero_rcv(t_game *g);
void			set_rcv(t_game *g, int x);
void			calculate_ray_dist(t_game *g);
void			perform_dda(t_game *g);

/*
**				draw.c
*/

void			draw_pixel(t_game *g, int x, int y, unsigned int color);
//void			draw_vertical_l(t_game *g, int len, int x, unsigned int color);
//void			draw_rectangle(t_game *g, int len, int x, unsigned int color);
void			draw_rec(t_game *g, int x, int y, unsigned int color);
void			draw_map(t_game *g);
void			draw_grid(t_game *g);

#endif
