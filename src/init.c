/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:47:27 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 16:47:29 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		first_empty_position(t_app *app)
{
	int		x;
	int		y;

	y = 0;
	while (y < app->map->height)
	{
		x = 0;
		while (x < app->map->width)
		{
			if (app->map->data[y][x] == 0)
			{
				app->pos = (t_v2){x + 0.1, y + 0.1};
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int		parse_arguments(int ac, char **av, t_app *app)
{
	if (ac < 2)
	{
		ft_putstr_fd("Usage: ./wolf3d [map file]\n", 2);
		return (1);
	}
	app->map = parse_map_file(av[1]);
	if (!app->map)
	{
		ft_putstr_fd("Error parsing map file\n", 2);
		return (1);
	}
	if (first_empty_position(app) != 0)
	{
		ft_putstr_fd("Could not find an empty starting position\n", 2);
		return (1);
	}
	return (0);
}

void	copy_textures_info(t_app *app, int width)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			y = 0;
			while (y < TEX_HEIGHT)
			{
				app->texture[i][x + TEX_WIDTH * y] =
					app->textures.data[x + width * y + (i * TEX_WIDTH)];
				y++;
			}
			x++;
		}
		i++;
	}
}

int		load_textures(t_app *app)
{
	int		width;
	int		height;

	app->textures.ptr = (int *)mlx_xpm_file_to_image(app->mlx,
		TEX_FILE_PATH, &width, &height);
	if (!app->textures.ptr)
	{
		ft_putstr_fd("Could not load textures file\n", 2);
		return (1);
	}
	if (width != TEX_WIDTH * NUM_TEXTURES || height != TEX_HEIGHT)
	{
		printf("%d %d\n", width, height);
		ft_putstr_fd("Invalid texture file format\n", 2);
		return (1);
	}
	app->textures.data = (int *)mlx_get_data_addr(app->textures.ptr,
		app->textures.infos, app->textures.infos + 1, app->textures.infos + 2);
	copy_textures_info(app, width);
	return (0);
}

int		init_app(t_app *app)
{
	memset(app, 0, sizeof(t_app));
	clock_init(&(app->clock));
	app->dir = (t_v2) { .x = 1, .y = 0 };
	app->plane = (t_v2) { .x = 0, .y = -0.66 };
	app->mlx = mlx_init();
	if (!app->mlx)
	{
		ft_putstr_fd("Couldn't init mlx\n", 2);
		return (1);
	}
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3d");
	if (!app->win)
	{
		ft_putstr_fd("Couldn't create window\n", 2);
		return (1);
	}
	mlx_expose_hook(app->win, loop_hook, app);
	app->image.ptr = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	app->image.data = (int *)mlx_get_data_addr(app->image.ptr, app->image.infos,
			app->image.infos + 1, app->image.infos + 2);
	mlx_loop_hook(app->mlx, loop_hook, app);
	mlx_hook(app->win, KEY_PRESS, KEY_PRESS_MASK, key_press_event, app);
	mlx_hook(app->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_event, app);
	return (0);
}
