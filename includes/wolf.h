/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:54:51 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 16:41:09 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <mlx.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_ESCAPE 53
# define TEX_FILE_PATH "./textures.xpm"

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

# define WIN_WIDTH 1200
# define WIN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define NUM_TEXTURES 4

# define MOVE_SPEED 0.005f
# define ROT_SPEED 0.0025f

# define ROOF_COLOR 0x666666
# define GROUND_COLOR 0x0

# define MAP_COORDS(APP, X, Y) ((int)((APP)->map->data[(int)(Y)][(int)(X)]))
# define PIXEL_AT(APP, C) (*(APP->image.data + (C.x + WIN_WIDTH * C.y)))

typedef struct		s_v2
{
	double x;
	double y;
}					t_v2;

typedef struct		s_v2i
{
	int x;
	int y;
}					t_v2i;

typedef struct		s_image
{
	void			*ptr;
	int				*data;
	int				infos[3];
}					t_image;

typedef struct		s_clock
{
	struct timeval	time;
	int				current_fps;
	int				last_tick_fps;
}					t_clock;

typedef enum		e_keys
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}					t_keys;

typedef enum		e_direction
{
	SOUTH,
	WEST,
	NORTH,
	EAST
}					t_direction;

typedef struct		s_map
{
	int				width;
	int				height;
	int				**data;
}					t_map;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_image			textures;
	t_v2			pos;
	t_v2			dir;
	t_v2			plane;
	t_clock			clock;
	int				key_pressed[4];
	int				texture[NUM_TEXTURES][TEX_WIDTH * TEX_HEIGHT];
	t_map			*map;
}					t_app;

typedef struct		s_ctx
{
	t_v2			camera;
	t_v2			ray_pos;
	t_v2			ray_dir;
	t_v2			delta_dist;
	t_v2			side_dist;
	t_v2i			map;
	t_v2i			step;
	t_v2i			tex;
	t_v2i			boundaries;
	double			line_height;
	double			wall_dist;
	t_direction		direction;
}					t_ctx;

int					clock_init(t_clock *clock);
float				clock_tick(t_clock *clock);

int					key_press_event(int keycode, t_app *app);
int					key_release_event(int keycode, t_app *app);

t_map				*parse_map_file(char *path);

int					loop_hook(t_app *app);
void				main_draw_loop(t_app *app);
int					loop_hook(t_app *app);

int					first_empty_position(t_app *app);
int					parse_arguments(int ac, char **av, t_app *app);
int					init_app(t_app *app);
int					load_textures(t_app *app);

void				free_map_data(t_map *map);
void				free_app(t_app *app);

void				move_character(t_app *app, float dt);

void				plot_line(t_app *app, t_ctx *ctx, t_v2i cursor);

#endif
