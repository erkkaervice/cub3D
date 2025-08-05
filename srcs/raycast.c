/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:55:14 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/05 18:09:58 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_basic(t_game *game, int x, t_ray *ray)
{
	float	camera_x;

	camera_x = 2.0f * x / (float)WIDTH - 1.0f;
	ray->ray_dir_x = game->dir_x + game->plane_x * camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * camera_x;
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30f;
	else
		ray->delta_dist_x = fabsf(1.0f / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30f;
	else
		ray->delta_dist_y = fabsf(1.0f / ray->ray_dir_y);
}

void	init_ray_steps(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - game->player_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - game->player_y)
			* ray->delta_dist_y;
	}
}

int	perform_dda(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0
			|| ray->map_x >= map_width(game->cfg->map[0])
			|| ray->map_y < 0
			|| ray->map_y >= map_height(game->cfg->map))
			return (0);
		if (game->cfg->map[ray->map_y][ray->map_x] == '1')
			return (1);
	}
}

static float	wall_maths(t_game *game, t_ray *ray, float *wall_x)
{
	float	perp_dist;

	if (ray->side == 0)
		perp_dist = (ray->map_x - game->player_x + (1 - ray->step_x)
				* 0.5f) / ray->ray_dir_x;
	else
		perp_dist = (ray->map_y - game->player_y + (1 - ray->step_y)
				* 0.5f) / ray->ray_dir_y;
	if (perp_dist < 0.001f)
		perp_dist = 0.001f;
	if (ray->side == 0)
		*wall_x = game->player_y + perp_dist * ray->ray_dir_y;
	else
		*wall_x = game->player_x + perp_dist * ray->ray_dir_x;
	*wall_x -= floorf(*wall_x);
	return (perp_dist);
}

void	calculate_wall(t_game *game, t_ray *ray, t_wall *wall)
{
	float	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	float	wall_x;

	perp_dist = wall_maths(game, ray, &wall_x);
	line_h = (int)(HEIGHT / perp_dist);
	if (line_h < 1)
		line_h = 1;
	draw_start = -line_h / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_h / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	wall->perp_wall_dist = perp_dist;
	wall->line_height = line_h;
	wall->draw_start = draw_start;
	wall->draw_end = draw_end;
	wall->tex_x = get_tex_x(game, ray, wall_x);
}
