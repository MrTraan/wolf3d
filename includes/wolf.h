/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:54:51 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/10 16:55:41 by ngrasset         ###   ########.fr       */
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
# define TEX_FILE_PATH "./textures/minecraft.xpm"

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

# define WIN_WIDTH 1200
# define WIN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define NUM_TEXTURES 8

# define MOVE_SPEED 0.1f
# define ROT_SPEED 0.05f

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

int					main_draw_loop(t_app *app);

int					clock_init(t_clock *clock);
int					clock_tick(t_clock *clock);

int					key_press_event(int keycode, t_app *app);
int					key_release_event(int keycode, t_app *app);

t_map				*parse_map_file(char *path);

int					loop_hook(t_app *app);
int					main_draw_loop(t_app *app);

int					first_empty_position(t_app *app);
int					parse_arguments(int ac, char **av, t_app *app);
int					init_app(t_app *app);
int					load_textures(t_app *app);

void				free_map_data(t_map *map);
void				free_app(t_app *app);
#endif
