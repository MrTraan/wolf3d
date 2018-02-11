/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:20:11 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 15:44:24 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int update(t_app *app, float dt)
{
	move_character(app, dt);
	return (0);
}

void clear_image(t_app *app)
{
	memset(app->image.data, 0, sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
}

int		loop_hook(t_app *app)
{
	float	dt;

	dt = clock_tick(&(app->clock));
	update(app, dt);
	clear_image(app);
	main_draw_loop(app);
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	return (0);
}

int		main(int ac, char **av)
{
	t_app		app;

	if (init_app(&app) || parse_arguments(ac, av, &app) || load_textures(&app))
	{
		free_app(&app);
		return (1);
	}
	main_draw_loop(&app);
	mlx_loop(app.mlx);
	return (0);
}
