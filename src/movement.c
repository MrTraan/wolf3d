/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:18:23 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/10 17:42:23 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void		apply_movement(t_app *app, t_v2 mov)
{
	if (app->pos.x + mov.x > 0 && app->pos.x + mov.x < app->map->width &&
		MAP_COORDS(app, app->pos.x + mov.x, app->pos.y) == 0)
		app->pos.x += mov.x;
	if (app->pos.y + mov.y > 0 && app->pos.y + mov.y < app->map->height &&
		MAP_COORDS(app, app->pos.x, app->pos.y + mov.y) == 0)
		app->pos.y += mov.y;
}

static void		apply_rotation(t_app *app, t_v2 rot)
{
	t_v2	old_dir;
	t_v2	old_plane;

	old_dir = app->dir;
	old_plane = app->plane;
	app->dir.x = app->dir.x * rot.x - app->dir.y * rot.y;
	app->dir.y = old_dir.x * rot.y + app->dir.y * rot.x;
	app->plane.x = app->plane.x * rot.x - app->plane.y * rot.y;
	app->plane.y = old_plane.x * rot.y + app->plane.y * rot.x;
}

void			move_character(t_app *app)
{
	t_v2 movement;

	if (app->key_pressed[UP])
	{
		movement.x = app->dir.x * MOVE_SPEED;
		movement.y = app->dir.y * MOVE_SPEED;
		apply_movement(app, movement);
	}
	if (app->key_pressed[DOWN])
	{
		movement.x = -app->dir.x * MOVE_SPEED;
		movement.y = -app->dir.y * MOVE_SPEED;
		apply_movement(app, movement);
	}
	if (app->key_pressed[LEFT])
	{
		movement = (t_v2) { cos(ROT_SPEED), sin(ROT_SPEED) };
		apply_rotation(app, movement);
	}
	if (app->key_pressed[RIGHT])
	{
		movement.x = cos(-ROT_SPEED);
		movement.y = sin(-ROT_SPEED);
		apply_rotation(app, movement);
	}
}
