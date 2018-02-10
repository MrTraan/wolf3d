/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:20:11 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/10 16:27:57 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int update(t_app *app)
{
	t_v2 new_pos;

	if (app->key_pressed[UP])
	{
		new_pos.x = app->pos.x + app->dir.x * MOVE_SPEED;
		if (new_pos.x > 0 && new_pos.x < app->map->width && app->map->data[(int)app->pos.y][(int)new_pos.x] == 0)
			app->pos.x += app->dir.x * MOVE_SPEED;
		new_pos.y = app->pos.y + app->dir.y * MOVE_SPEED;
		if (new_pos.y > 0 && new_pos.y < app->map->height && app->map->data[(int)new_pos.y][(int)app->pos.x] == 0)
			app->pos.y += app->dir.y * MOVE_SPEED;
	}
	if (app->key_pressed[DOWN])
	{
		new_pos.x = app->pos.x - app->dir.x * MOVE_SPEED;
		if (new_pos.x > 0 && new_pos.x < app->map->width && app->map->data[(int)app->pos.y][(int)new_pos.x] == 0)
			app->pos.x -= app->dir.x * MOVE_SPEED;
		new_pos.y = app->pos.y - app->dir.y * MOVE_SPEED;
		if (new_pos.y > 0 && new_pos.y < app->map->height && app->map->data[(int)new_pos.y][(int)app->pos.x] == 0)
			app->pos.y -= app->dir.y * MOVE_SPEED;
	}
	if (app->key_pressed[LEFT])
	{
		double oldDirX = app->dir.x;
		app->dir.x = app->dir.x * cos(ROT_SPEED) -
			app->dir.y * sin(ROT_SPEED);
		app->dir.y = oldDirX * sin(ROT_SPEED) +
			app->dir.y * cos(ROT_SPEED);
		double oldPlaneX = app->plane.x;
		app->plane.x = app->plane.x * cos(ROT_SPEED) -
			app->plane.y * sin(ROT_SPEED);
		app->plane.y = oldPlaneX * sin(ROT_SPEED) +
			app->plane.y * cos(ROT_SPEED);
	}
	if (app->key_pressed[RIGHT])
	{
		double oldDirX = app->dir.x;
		app->dir.x = app->dir.x * cos(-ROT_SPEED) -
			app->dir.y * sin(-ROT_SPEED);
		app->dir.y = oldDirX * sin(-ROT_SPEED) +
			app->dir.y * cos(-ROT_SPEED);
		double oldPlaneX = app->plane.x;
		app->plane.x = app->plane.x * cos(-ROT_SPEED) -
			app->plane.y * sin(-ROT_SPEED);
		app->plane.y = oldPlaneX * sin(-ROT_SPEED) +
			app->plane.y * cos(-ROT_SPEED);
	}
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

		t_v2 deltaDist = {
			.x = sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
			.y = sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y))
		};

		double perpWallDist;

		t_v2i step;

		int hit = 0;
		int side;

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
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				map.y += step.y;
				side = 1;
			}
			if (map.y >= app->map->height || map.y < 0 || map.x >= app->map->width || map.x < 0)
				hit = 1;
			else if (app->map->data[map.y][map.x] > 0)
				hit = 1;
		}

		if (side == 0)
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

		int texNum;
		
		if (map.y >= app->map->height || map.y < 0 || map.x >= app->map->width || map.x < 0)
			texNum = 0;
		else
			texNum = app->map->data[map.y][map.x] - 1;

		double wallX;
		if (side == 0) wallX = rayPos.y + perpWallDist * rayDir.y;
		else wallX = rayPos.x + perpWallDist * rayDir.x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)TEX_WIDTH);
		if (side == 0 && rayDir.x > 0)
			texX = TEX_WIDTH - texX - 1;
		if (side == 1 && rayDir.y < 0)
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
			*(app->image.data + (x + WIN_WIDTH * y)) =
				(int)mlx_get_color_value(app->mlx, 0x0);
		}
		for (int y = start; y < end; y++)
		{
			int d = y * 256 - WIN_HEIGHT * 128 + lineHeight * 128;
			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
			if (texY < 0 || texY > TEX_HEIGHT)
				texY = 0;
			if (texX < 0 || texX > TEX_HEIGHT)
				texX = 0;
			int color = app->texture[texNum][TEX_WIDTH * texY + texX];
			if (side == 1)
				color = (color >> 1) & 0x7F7F7F;
			*(app->image.data + (x + WIN_WIDTH * y)) =
				(int)mlx_get_color_value(app->mlx, color);
		}
		for (int y = end; y < WIN_HEIGHT - 1; y++)
		{
			*(app->image.data + (x + WIN_WIDTH * y)) =
				(int)mlx_get_color_value(app->mlx, 0x666666);
		}
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	mlx_put_image_to_window(app->mlx, app->win, app->textures.ptr, 0, 0);
	return (0);
}

int		loop_hook(t_app *app)
{
	int		fps;
	char	buffer[1024];

	update(app);
	main_draw_loop(app);
	fps = clock_tick(&(app->clock));
	sprintf(buffer, "%d fps", fps);
	mlx_string_put(app->mlx, app->win, 12, 12, 0xFFFFFF, buffer);
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
