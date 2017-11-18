/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:20:11 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/18 20:20:18 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int keyhook(int keycode, t_app *app)
{
	double moveSpeed = 0.5f;
	double rotSpeed = 0.2f;

	if (keycode == KEY_UP)
	{
		if (worldMap[(int)(app->pos.x + app->dir.x * moveSpeed)][(int)app->pos.y] == 0)
			app->pos.x += app->dir.x * moveSpeed;
		if (worldMap[(int)app->pos.x][(int)(app->pos.y + app->dir.y * moveSpeed)] == 0)
			app->pos.y += app->dir.y * moveSpeed;
	}
	if (keycode == KEY_DOWN)
	{
		if (worldMap[(int)(app->pos.x - app->dir.x * moveSpeed)][(int)app->pos.y] == 0)
			app->pos.x -= app->dir.x * moveSpeed;
		if (worldMap[(int)app->pos.x][(int)(app->pos.y - app->dir.y * moveSpeed)] == 0)
			app->pos.y -= app->dir.y * moveSpeed;
	}
	if (keycode == KEY_LEFT)
	{
		double oldDirX = app->dir.x;
		app->dir.x = app->dir.x * cos(rotSpeed) -
			app->dir.y * sin(rotSpeed);
		app->dir.y = oldDirX * sin(rotSpeed) +
			app->dir.y * cos(rotSpeed);
		double oldPlaneX = app->plane.x;
		app->plane.x = app->plane.x * cos(rotSpeed) -
			app->plane.y * sin(rotSpeed);
		app->plane.y = oldPlaneX * sin(rotSpeed) +
			app->plane.y * cos(rotSpeed);
	}
	if (keycode == KEY_RIGHT)
	{
		double oldDirX = app->dir.x;
		app->dir.x = app->dir.x * cos(-rotSpeed) -
			app->dir.y * sin(-rotSpeed);
		app->dir.y = oldDirX * sin(-rotSpeed) +
			app->dir.y * cos(-rotSpeed);
		double oldPlaneX = app->plane.x;
		app->plane.x = app->plane.x * cos(-rotSpeed) -
			app->plane.y * sin(-rotSpeed);
		app->plane.y = oldPlaneX * sin(-rotSpeed) +
			app->plane.y * cos(-rotSpeed);
	}
	main_draw_loop(app);
	return (0);
}

int drawVerLine(t_app *app, int x, int start, int end, int color)
{
	if (start > end)
	{
		int tmp = start;
		start = end;
		end = tmp;
	}
	for (int y = 0; y < start; y++)
	{
		*(app->image.data + (x + WIN_WIDTH * y)) =
			(int)mlx_get_color_value(app->mlx, 0x001c49);
	}
	for (int y = start; y < end; y++)
	{
		*(app->image.data + (x + WIN_WIDTH * y)) =
			(int)mlx_get_color_value(app->mlx, color);
	}
	for (int y = end; y < WIN_HEIGHT - 1; y++)
	{
		*(app->image.data + (x + WIN_WIDTH * y)) =
			(int)mlx_get_color_value(app->mlx, 0x666666);
	}
	return (0);
}

void clear_image(t_app *app)
{
	for (int x = 0; x < WIN_WIDTH; x++)
		drawVerLine(app, x, 0, WIN_HEIGHT - 1, 0); 
}


int main_draw_loop(t_app *app)
{
	/* double time = 0; */
	/* double oldTime = 0; */
	clear_image(app);

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		t_v2 camera = { .x = 2 * x / (double)WIN_WIDTH - 1, .y = 0 };
		t_v2 rayPos = { .x = app->pos.x, .y = app->pos.y };
		t_v2 rayDir = { .x = app->dir.x + app->plane.x * camera.x,
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

			if (worldMap[map.x][map.y] > 0)
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

		int color;
		
		switch(worldMap[map.x][map.y])
		{
			case 1: color = 0xFF0000; break;
			case 2: color = 0x00FF00; break;
			case 3: color = 0x0000FF; break;
			case 4: color = 0xFFFFFF; break;
			default: color = 0xFF00FF; break;
		}

		if (side == 1)
			color /= 2;
		drawVerLine(app, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	return (0);
}

int		main(void)
{
	t_app		app;

	memset(&app, 0, sizeof(t_app));
	app.pos = (t_v2) { .x = 22, .y = 12 };
	app.dir = (t_v2) { .x = -1, .y = 0 };
	app.plane = (t_v2) { .x = 0, .y = 0.66 };

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3d");
	mlx_expose_hook(app.win, main_draw_loop, &app);
	app.image.ptr = mlx_new_image(app.mlx, WIN_WIDTH, WIN_HEIGHT);
	app.image.data = (int *)mlx_get_data_addr(app.image.ptr, app.image.infos,
			app.image.infos + 1, app.image.infos + 2);
	mlx_key_hook(app.win, keyhook, &app);
	main_draw_loop(&app);
	mlx_loop(app.mlx);
	return (0);
}
