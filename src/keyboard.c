/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 12:55:45 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/10 16:20:59 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int			key_press_event(int keycode, t_app *app)
{
	if (keycode == KEY_UP)
		app->key_pressed[UP] = 1;
	if (keycode == KEY_DOWN)
		app->key_pressed[DOWN] = 1;
	if (keycode == KEY_LEFT)
		app->key_pressed[LEFT] = 1;
	if (keycode == KEY_RIGHT)
		app->key_pressed[RIGHT] = 1;
	if (keycode == KEY_ESCAPE)
	{
		free_app(app);
		exit(0);
	}
	return (0);
}

int			key_release_event(int keycode, t_app *app)
{
	if (keycode == KEY_UP)
		app->key_pressed[UP] = 0;
	if (keycode == KEY_DOWN)
		app->key_pressed[DOWN] = 0;
	if (keycode == KEY_LEFT)
		app->key_pressed[LEFT] = 0;
	if (keycode == KEY_RIGHT)
		app->key_pressed[RIGHT] = 0;
	return (0);
}

