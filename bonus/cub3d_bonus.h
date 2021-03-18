/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:05:38 by tjung             #+#    #+#             */
/*   Updated: 2021/03/19 04:05:52 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include "./gnl_bonus/get_next_line_bonus.h"

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_MOTION_NOTIFY		6
# define X_EVENT_KEY_EXIT			17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_CLK_M		2

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
	unsigned int	*ii;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct	s_map {
	char	**tab;
	t_ivec	size;
	int		spr;
	int		max_x;
	t_ivec	minimap;
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

typedef struct	s_sprite
{
	double	x;
	double	y;
	char	type;
}				t_sprite;

typedef struct	s_spr_config {
	double		transform_y;
	int			sprite_scr_x;
	int			v_move_scr;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	t_sprite	sprite;
	t_ivec		s_color;
}				t_spr_config;

typedef struct	s_game {
	t_screen		scr;
	t_flag			flag;
	t_p_move		p_move;
	t_tex			tex;
	t_map			map;
	t_player		p;
	t_sprite		*spr;
	t_raycasting	rc;
	t_spr_config	sc;
	unsigned int	**buffer;
	time_t			t;
	long			st;
	int				m;
}				t_game;

/*
**				main_bonus.c
*/

int				print_error(int e, char *msg);
int				check_file_name(char *s, char *extension);

/*
**				cub3d_bonus.c
*/

int				start_cub3d(char *file, int bmp);

/*
**				tools_bonus.c
*/

int				malloc_buffer(t_game *g);
int				main_loop(t_game *g);
int				exit_hook(t_game *g);
int				close_cub3d(t_game *g, int win);

/*
**				parse_bonus.c
*/

int				parse_cube_file(char *file, t_game *g);
int				valid_line(char *line, int start);

/*
**				parse_tools_bonus.c
*/

int				parse_map(t_game *g, char *line, int *i);
int				parse_resolution(t_game *g, char *line, int *i);
int				parse_tex(t_game *g, unsigned int **tex, char *line, int *i);
int				parse_color(t_game *g, unsigned int *color, char *line, int *i);

/*
**				parse_tools_details_bonus.c
*/

char			*parse_row(t_game *g, char *line, int *i);
void			set_player_config(t_game *g);
int				set_sprites_config(t_game *g);
void			set_plane_values(t_game *g);

/*
**				parse_check_bonus.c
*/

int				parse_check(t_game *g);

/*
**				bitmap_bonus.c
*/

int				make_bitmap(t_game *g, unsigned int **buffer);

/*
**				engine_bonus.c
*/

void			set_color_to_buffer(
					unsigned int **buffer, int x, int y, unsigned int color);
int				print_image_to_buffer(
					t_game *g, unsigned int **buffer, double *z_depth);
int				start_engine(t_game *g, unsigned int **buffer);

/*
**				raycasting_bonus.c
*/

void			init_zero_rcv(t_game *g);
int				get_line_height(t_game *g, int x, double *z_depth);

/*
**				draw_bonus.c
*/

void			draw_buffer(t_game *g, unsigned int **buffer);
void			draw_rectangle_to_buffer(t_game *g,
						int scale, unsigned int **buffer, unsigned int color);
void			draw_map_to_buffer(t_game *g, unsigned int **buffer);

/*
**				draw_details_bonus.c
*/

void			draw_player_to_buffer(t_game *g, int s, unsigned int **buffer);

/*
**				key_bonus.c
*/

void			move_view(t_game *g, double delta_x, double delta_y);
void			rotate_view(int keycode, t_game *g, double speed);
int				key_mouse(int mouse_x, int mouse_y, t_game *g);
int				key_press(int keycode, t_game *g);
int				key_release(int keycode, t_game *g);

/*
**				sprite_bonus.c
*/

int				print_sprite_to_buffer(
						t_game *g, unsigned int **buffer, double *z_depth);

/*
**				sprite_details_bonus.c
*/

void			calculate_spr_values(
					t_game *g, double sprite_x, double sprite_y);
int				get_sprite_color(t_game *g,
					int *stripe, unsigned int **buffer, double *z_depth);

/*
**				time_bar.c
*/

int				make_time_bar(t_game *g, unsigned int **buffer, int win);

/*
**				bgm_bonus.c
*/

void			run_bgm(void);

/*
**				init_zero_bonus.c
*/

void			init_zero(t_game *g);

#endif
