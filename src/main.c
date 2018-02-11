/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:20:11 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 15:12:56 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>
# define VEC_SQRT(v) (sqrt(v.x * v.x + v.y * v.y))
# define ANGLE(v1, v2) (( v1.x * v2.x + v1.y * v2.y ) / (VEC_SQRT(v1) * VEC_SQRT(v2)))

int update(t_app *app, float dt)
{
	move_character(app, dt);
	return (0);
}

void clear_image(t_app *app)
{
	memset(app->image.data, 0, sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
}

int main_draw_loop(t_app *app)
{
	clear_image(app);

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		t_v2 camera = { .x = 2 * x / (double)WIN_WIDTH - 1, .y = 0 };
		t_v2 rayPos = { .x = app->pos.x, .y = app->pos.y };
		t_v2 rayDir = {
			.x = app->dir.x + app->plane.x * camera.x,
			.y = app->dir.y + app->plane.y * camera.x
		};

		t_v2i map = { .x = (int)rayPos.x, .y = (int)rayPos.y };

		t_v2 sideDist;

		/* t_v2 deltaDist = { */
		/* 	.x = sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)), */
		/* 	.y = sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)) */
		/* }; */
		t_v2 deltaDist = {
			.x = fabs(1 / rayDir.x),
			.y = fabs(1 / rayDir.y)
		};

		double perpWallDist;

		t_v2i step;

		int hit = 0;
		t_direction direction;

		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (rayPos.x - map.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map.x + 1.0 - rayPos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			step.y = -1;
			sideDist.y = (rayPos.y - map.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0 - rayPos.y) * deltaDist.y;
		}

		while (hit == 0)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				map.x += step.x;
				direction = step.x == -1 ? EAST : WEST;
			}
			else
			{
				sideDist.y += deltaDist.y;
				map.y += step.y;
				direction = step.y == -1 ? NORTH : SOUTH;
			}
			if (map.y >= app->map->height || map.y < 0 || map.x >= app->map->width || map.x < 0)
				hit = 1;
			else if (app->map->data[map.y][map.x] > 0)
				hit = 1;
		}
		if (direction == WEST || direction == EAST)
			perpWallDist = (map.x - rayPos.x + (1 - step.x) / 2) / rayDir.x;
		else
			perpWallDist = (map.y - rayPos.y + (1 - step.y) / 2) / rayDir.y;

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		int texNum = direction;

		double wallX;
		if (direction == WEST || direction == EAST)
			wallX = rayPos.y + perpWallDist * rayDir.y;
		else
			wallX = rayPos.x + perpWallDist * rayDir.x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)TEX_WIDTH);
		if ((direction == WEST || direction == EAST) && rayDir.x > 0)
			texX = TEX_WIDTH - texX - 1;
		if ((direction == NORTH || direction == SOUTH) && rayDir.y > 0)
			texX = TEX_WIDTH - texX - 1;

		int start = drawStart;
		int end = drawEnd;

		if (start > end)
		{
			int tmp = start;
			start = end;
			end = tmp;
		}
		for (int y = 0; y < start; y++)
		{
			PIXEL_AT(app, x, y) = (int)mlx_get_color_value(app->mlx, GROUND_COLOR);
		}
		for (int y = start; y < end; y++)
		{
			int d = y * 256 - WIN_HEIGHT * 128 + lineHeight * 128;
			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
			if (texY < 0 || texY > TEX_HEIGHT)
				texY = 0;
			if (texX < 0 || texX > TEX_HEIGHT)
				texX = 0;
			int color;
			color = app->texture[texNum][TEX_WIDTH * texY + texX];
			PIXEL_AT(app, x, y) = (int)mlx_get_color_value(app->mlx, color);
		}
		for (int y = end; y < WIN_HEIGHT - 1; y++)
		{
			PIXEL_AT(app, x, y) = (int)mlx_get_color_value(app->mlx, ROOF_COLOR);
		}
	}
	return (0);
}

int		loop_hook(t_app *app)
{
	float	dt;
	char	buffer[1024];

	dt = clock_tick(&(app->clock));
	update(app, dt);
	main_draw_loop(app);
	
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	sprintf(buffer, "%d fps", app->clock.last_tick_fps);
	mlx_string_put(app->mlx, app->win, 12, 12, 0xFFFFFF, buffer);
	sprintf(buffer, "dir: %f %f", app->dir.x, app->dir.y);
	mlx_string_put(app->mlx, app->win, 12, 24, 0xFFFFFF, buffer);
	sprintf(buffer, "pos: %f %f", app->pos.x, app->pos.y);
	mlx_string_put(app->mlx, app->win, 12, 36, 0xFFFFFF, buffer);
	sprintf(buffer, "plane: %f %f", app->plane.x, app->plane.y);
	mlx_string_put(app->mlx, app->win, 12, 48, 0xFFFFFF, buffer);
	sprintf(buffer, "length dir: %f", VEC_SQRT(app->dir));
	mlx_string_put(app->mlx, app->win, 12, 60, 0xFFFFFF, buffer);
	sprintf(buffer, "length plane: %f", VEC_SQRT(app->plane));
	mlx_string_put(app->mlx, app->win, 12, 72, 0xFFFFFF, buffer);
	sprintf(buffer, "fov: %f", acos(ANGLE(app->plane, app->dir)) * 180 / M_PI);
	mlx_string_put(app->mlx, app->win, 12, 90, 0xFFFFFF, buffer);

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
