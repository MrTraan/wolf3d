/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:20:11 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/19 16:51:21 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int worldMap[mapWidth][mapHeight]=
{
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	{4,0,0,5,0,0,0,0,0,4,1,0,1,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

int update(t_app *app)
{
	double moveSpeed = 0.1f;
	double rotSpeed = 0.05f;

	if (app->key_pressed[UP])
	{
		if (worldMap[(int)(app->pos.x + app->dir.x * moveSpeed)][(int)app->pos.y] == 0)
			app->pos.x += app->dir.x * moveSpeed;
		if (worldMap[(int)app->pos.x][(int)(app->pos.y + app->dir.y * moveSpeed)] == 0)
			app->pos.y += app->dir.y * moveSpeed;
	}
	if (app->key_pressed[DOWN])
	{
		if (worldMap[(int)(app->pos.x - app->dir.x * moveSpeed)][(int)app->pos.y] == 0)
			app->pos.x -= app->dir.x * moveSpeed;
		if (worldMap[(int)app->pos.x][(int)(app->pos.y - app->dir.y * moveSpeed)] == 0)
			app->pos.y -= app->dir.y * moveSpeed;
	}
	if (app->key_pressed[LEFT])
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
	if (app->key_pressed[RIGHT])
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
	return (0);
}

void clear_image(t_app *app)
{
	memset(app->image.data, 0, sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	/* for (int x = 0; x < WIN_WIDTH; x++) */
	/* 	drawVerLine(app, x, 0, WIN_HEIGHT - 1, 0); */ 
}


int main_draw_loop(t_app *app)
{
	clear_image(app);
	update(app);

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

		int texNum = worldMap[map.x][map.y] - 1;

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
				(int)mlx_get_color_value(app->mlx, 0x001c49);
		}
		for (int y = start; y < end; y++)
		{
			int d = y * 256 - WIN_HEIGHT * 128 + lineHeight * 128;
			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
			if (texNum < 0 || texNum > 7) {
				printf("texnum error: %d\n", texNum);
			}
			if (texY < 0 || texY > TEX_HEIGHT) {
				printf("texY error: %d\n", texY);
				printf("%d %d\n", d, lineHeight);
			}
			if (texX < 0 || texX > TEX_HEIGHT) {
				printf("texX error: %d\n", texX);
			}
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

	main_draw_loop(app);
	fps = clock_tick(&(app->clock));

	char buffer[100];
	sprintf(buffer, "%d fps", fps);
	mlx_string_put(app->mlx, app->win, 12, 12, 0xFFFFFF, buffer);

	return (0);
}

int		main(void)
{
	t_app		app;

	memset(&app, 0, sizeof(t_app));

	clock_init(&(app.clock));
	app.pos = (t_v2) { .x = 22, .y = 11.5 };
	app.dir = (t_v2) { .x = -1, .y = 0 };
	app.plane = (t_v2) { .x = 0, .y = 0.66 };

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3d");


	int a, b;
	app.textures.ptr = (int *)mlx_xpm_file_to_image(app.mlx, "./textures/wolftextures.xpm", &a, &b);
	printf("%d %d %p\n", a, b, app.textures.ptr);
	app.textures.data = (int *)mlx_get_data_addr(app.textures.ptr, app.textures.infos, app.textures.infos + 1, app.textures.infos + 2);

	/* int *textures = app.textures.data; */

	for (int i = 0; i < 8; i++) {
		for(int x = 0; x < TEX_WIDTH; x++)
			for(int y = 0; y < TEX_HEIGHT; y++)
			{

				app.texture[i][x + TEX_WIDTH * y] = app.textures.data[x + a * y + (i * TEX_WIDTH)];
				/* printf("accessing %d %d of texture and %d %d of file\n", x, y, x + (i * TEX_WIDTH), y); */
				/* printf("index %d and %d\n", x + TEX_WIDTH * y, x + (i * TEX_WIDTH) + TEX_WIDTH * y); */
				/* app.texture[i][x + TEX_WIDTH * y] = textures[x + (i * TEX_WIDTH) + TEX_WIDTH * y]; */
			}
	}


	mlx_expose_hook(app.win, main_draw_loop, &app);
	app.image.ptr = mlx_new_image(app.mlx, WIN_WIDTH, WIN_HEIGHT);
	app.image.data = (int *)mlx_get_data_addr(app.image.ptr, app.image.infos,
			app.image.infos + 1, app.image.infos + 2);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_hook(app.win, KEY_PRESS, KEY_PRESS_MASK, key_press_event, &app);
	mlx_hook(app.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_event, &app);
	main_draw_loop(&app);
	mlx_loop(app.mlx);
	return (0);
}
