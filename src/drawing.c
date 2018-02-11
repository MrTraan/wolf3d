/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:22:06 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 16:41:47 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void		setup_step(t_ctx *ctx)
{
	if (ctx->ray_dir.x < 0)
	{
		ctx->step.x = -1;
		ctx->side_dist.x = (ctx->ray_pos.x - ctx->map.x) *
			ctx->delta_dist.x;
	}
	else
	{
		ctx->step.x = 1;
		ctx->side_dist.x = (ctx->map.x + 1.0 - ctx->ray_pos.x) *
			ctx->delta_dist.x;
	}
	if (ctx->ray_dir.y < 0)
	{
		ctx->step.y = -1;
		ctx->side_dist.y = (ctx->ray_pos.y - ctx->map.y) *
			ctx->delta_dist.y;
	}
	else
	{
		ctx->step.y = 1;
		ctx->side_dist.y = (ctx->map.y + 1.0 - ctx->ray_pos.y) *
			ctx->delta_dist.y;
	}
}

static void		setup_ctx(t_app *app, t_ctx *ctx, int x)
{
	ctx->camera = (t_v2){ .x = 2 * x / (double)WIN_WIDTH - 1, .y = 0 };
	ctx->ray_pos = (t_v2){ .x = app->pos.x, .y = app->pos.y };
	ctx->ray_dir = (t_v2){
		.x = app->dir.x + app->plane.x * ctx->camera.x,
		.y = app->dir.y + app->plane.y * ctx->camera.x
	};
	ctx->delta_dist = (t_v2){
		.x = fabs(1 / ctx->ray_dir.x),
		.y = fabs(1 / ctx->ray_dir.y)
	};
	ctx->map = (t_v2i){
		.x = (int)ctx->ray_pos.x,
		.y = (int)ctx->ray_pos.y
	};
}

static void		find_collision(t_app *app, t_ctx *ctx)
{
	while (42)
	{
		if (ctx->side_dist.x < ctx->side_dist.y)
		{
			ctx->side_dist.x += ctx->delta_dist.x;
			ctx->map.x += ctx->step.x;
			ctx->direction = ctx->step.x == -1 ? EAST : WEST;
		}
		else
		{
			ctx->side_dist.y += ctx->delta_dist.y;
			ctx->map.y += ctx->step.y;
			ctx->direction = ctx->step.y == -1 ? NORTH : SOUTH;
		}
		if (ctx->map.y >= app->map->height || ctx->map.y < 0
			|| ctx->map.x >= app->map->width || ctx->map.x < 0
			|| app->map->data[ctx->map.y][ctx->map.x] == 1)
			break ;
	}
	if (ctx->direction == WEST || ctx->direction == EAST)
		ctx->wall_dist = (ctx->map.x - ctx->ray_pos.x +
				(1 - ctx->step.x) / 2) / ctx->ray_dir.x;
	else
		ctx->wall_dist = (ctx->map.y - ctx->ray_pos.y +
				(1 - ctx->step.y) / 2) / ctx->ray_dir.y;
}

void			map_boundaries(t_ctx *ctx)
{
	double wall_mapped_x;

	ctx->line_height = (int)(WIN_HEIGHT / ctx->wall_dist);
	ctx->boundaries.x = -ctx->line_height / 2 + WIN_HEIGHT / 2;
	if (ctx->boundaries.x < 0)
		ctx->boundaries.x = 0;
	ctx->boundaries.y = ctx->line_height / 2 + WIN_HEIGHT / 2;
	if (ctx->boundaries.y >= WIN_HEIGHT)
		ctx->boundaries.y = WIN_HEIGHT - 1;
	if (ctx->direction == WEST || ctx->direction == EAST)
		wall_mapped_x = ctx->ray_pos.y + ctx->wall_dist * ctx->ray_dir.y;
	else
		wall_mapped_x = ctx->ray_pos.x + ctx->wall_dist * ctx->ray_dir.x;
	wall_mapped_x -= floor(wall_mapped_x);
	ctx->tex.x = (int)(wall_mapped_x * (double)TEX_WIDTH);
	if ((ctx->direction == WEST || ctx->direction == EAST) &&
			ctx->ray_dir.x > 0)
		ctx->tex.x = TEX_WIDTH - ctx->tex.x - 1;
	if ((ctx->direction == NORTH || ctx->direction == SOUTH)
			&& ctx->ray_dir.y > 0)
		ctx->tex.x = TEX_WIDTH - ctx->tex.x - 1;
}

void			main_draw_loop(t_app *app)
{
	t_ctx		ctx;
	t_v2i		cursor;

	cursor = (t_v2i){0, 0};
	while (cursor.x < WIN_WIDTH)
	{
		cursor.y = 0;
		setup_ctx(app, &ctx, cursor.x);
		setup_step(&ctx);
		find_collision(app, &ctx);
		map_boundaries(&ctx);
		while (cursor.y < WIN_HEIGHT)
		{
			if (cursor.y < ctx.boundaries.x)
				PIXEL_AT(app, cursor) =
					(int)mlx_get_color_value(app->mlx, GROUND_COLOR);
			else if (cursor.y < ctx.boundaries.y)
				plot_line(app, &ctx, cursor);
			else
				PIXEL_AT(app, cursor) =
					(int)mlx_get_color_value(app->mlx, ROOF_COLOR);
			cursor.y++;
		}
		cursor.x++;
	}
}
