/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:18:52 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/18 20:20:44 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#define mapWidth 24
#define mapHeight 24
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#include <mlx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>   
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123

typedef struct	s_v2
{
	double x;
	double y;
}				t_v2;

typedef struct	s_v2i
{
	int x;
	int y;
}				t_v2i;

typedef struct		s_image
{
	void			*ptr;
	int				*data;
	int				infos[3];
}					t_image;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_v2 			pos;
	t_v2 			dir;
	t_v2 			plane;
}					t_app;

int main_draw_loop(t_app *app);

#endif
