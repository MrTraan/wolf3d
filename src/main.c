/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:20:11 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 16:41:24 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	clear_image(t_app *app)
{
	ft_memset(app->image.data, 0, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
}

void	plot_line(t_app *app, t_ctx *ctx, t_v2i cursor)
{
	int		d;
	int		color;

	d = cursor.y * 256 - WIN_HEIGHT * 128 + ctx->line_height * 128;
	ctx->tex.y = ((d * TEX_HEIGHT) / ctx->line_height) / 256;
	if (ctx->tex.y < 0 || ctx->tex.y > TEX_HEIGHT)
		ctx->tex.y = 0;
	if (ctx->tex.x < 0 || ctx->tex.x > TEX_HEIGHT)
		ctx->tex.x = 0;
	color = app->texture[ctx->direction][TEX_WIDTH * ctx->tex.y + ctx->tex.x];
	PIXEL_AT(app, cursor) = (int)mlx_get_color_value(app->mlx, color);
}

int		update(t_app *app, float dt)
{
	move_character(app, dt);
	return (0);
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

	if (init_app(&app) || parse_arguments(ac, av, &app) ||
		load_textures(&app))
	{
		free_app(&app);
		return (1);
	}
	main_draw_loop(&app);
	mlx_loop(app.mlx);
	return (0);
}
