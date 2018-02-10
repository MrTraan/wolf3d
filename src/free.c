/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:51:34 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/10 16:39:34 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void		free_map_data(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->height && map->data)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	free(map);
}

void		free_app(t_app *app)
{
	if (app->map)
		free_map_data(app->map);
	if (app->image.ptr)
		mlx_destroy_image(app->mlx, app->image.ptr);
	if (app->textures.ptr)
		mlx_destroy_image(app->mlx, app->textures.ptr);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
}
