/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:05:38 by tjung             #+#    #+#             */
/*   Updated: 2021/03/14 06:45:31 by tjung            ###   ########.fr       */
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

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_LEFT		123
# define KEY_RIGHT		124

# define U_DIV	1
# define V_DIV	1
# define V_MOVE 0.0

typedef struct	s_fvec {
	double	x;
	double	y;
}				t_fvec;

typedef struct	s_ivec {
	int		x;
	int		y;
}				t_ivec;

typedef struct	s_img {
	void	*ptr;
	char	*adr;
	int		bpp;
	int		sl;
	int		endian;
}				t_img;

typedef struct	s_screen {
	void	*mlx;
	void	*win;
	t_img	img;
	t_ivec	size;
}				t_screen;

typedef struct	s_flag {
	int		err;
	int		m;
	int		pnum;
}				t_flag;

typedef struct	s_p_move {
	int		y_move;
	int		x_move;
	int		rotate;
}				t_p_move;

typedef struct	s_tex {
	double			tex_pos;
	int				tex_x;
	int				tex_y;
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
	t_ivec	size;
	int		spr;
}				t_map;

typedef struct	s_player {
	t_fvec	pos;
	t_fvec	dir;
	t_fvec	o_dir;
	t_fvec	plane;
	t_fvec	o_plane;
}				t_player;

typedef struct	s_raycasting {
	double	camera_x;
	t_fvec	ray_dir;
	t_fvec	delta_dist;
	t_fvec	side_dist;
	double	perp_wall_dist;
	t_ivec	map;
	t_ivec	step;
	int		hit;
	int		side;
	int		hit_x;
	int		hit_y;
	double	wall_x;
	int		draw_start;
	int		draw_end;
}				t_raycasting;

typedef struct	s_spr_config {
	double	transform_y;
	int		sprite_scr_x;
	int		v_move_scr;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	t_fvec	sprite;
	t_ivec	s_color;
}				t_spr_config;

typedef struct	s_game {
	t_screen		scr;
	t_flag			flag;
	t_p_move		p_move;
	t_tex			tex;
	t_map			map;
	t_player		p;
	t_fvec			*spr;
	t_raycasting	rc;
	t_spr_config	sc;
	unsigned int	**buffer;
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

void			init_zero_scr(t_screen *scr);
void			init_zero_tex(t_tex *tex);
void			init_zero_map(t_map *map);
void			init_zero(t_game *g);
int				start_cub3d(char *file, int bmp);

/*
**				tools.c
*/

int				malloc_buffer(t_game *g);
int				main_loop(t_game *g);
int				exit_hook(t_game *g);
int				close_cub3d(t_game *g, int win);

/*
**				parse.c
*/

int				parse_cube_file(char *file, t_game *g);
int				parse_line(t_game *g, char *line);

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
void			set_plane_values(t_game *g);

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

void			calculate_tex_pos(t_game *g, int line_h, double *step);
void			set_color_to_buffer(
					unsigned int **buffer, int x, int y, unsigned int color);
unsigned int	get_color(t_game *g);
int				print_image_to_buffer(
					t_game *g, unsigned int **buffer, double *z_depth);
int				start_engine(t_game *g, unsigned int **buffer);

/*
**				raycasting.c
*/

void			init_zero_rcv(t_game *g);
void			set_rcv(t_game *g, int x);
void			calculate_ray_dist(t_game *g);
void			perform_dda(t_game *g);
int				get_line_height(t_game *g, int x, double *z_depth);

/*
**				draw.c
*/

void			draw_pixel(t_game *g, int x, int y, unsigned int color);
void			draw_buffer(t_game *g, unsigned int **buffer);
void			draw_vertical_l(t_game *g, int len, int x, unsigned int color);

/*
**				key.c
*/

void			move_view(t_game *g, double delta_x, double delta_y);
void			rotate_view(int keycode, t_game *g);
int				key_press(int keycode, t_game *g);
int				key_release(int keycode, t_game *g);

/*
**				sprite.c
*/

void			init_zero_scv(t_game *g);
void			get_sprites(t_game *g,
					int *sprite_order, unsigned int **buffer, double *z_depth);
int				print_sprite_to_buffer(
						t_game *g, unsigned int **buffer, double *z_depth);

/*
**				sprite_details.c
*/

void			descending_sort(int *order, double *dist, int amount);
void			sort_sprites(
					t_game *g, int *sprite_order, double *sprite_distance);
void			calculate_spr_pos(t_game *g);
void			calculate_spr_values(
					t_game *g, double sprite_x, double sprite_y);
int				get_sprite_color(t_game *g,
					int *stripe, unsigned int **buffer, double *z_depth);

#endif
