/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:55:14 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/06 15:59:11 by eala-lah         ###   ########.fr       */
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
	if (ray->ray_dir_x == 0.0f)
		ray->delta_dist_x = INFINITY;
	else
	{
		camera_x = ray->ray_dir_x;
		if (camera_x < 0.0f)
			camera_x = -camera_x;
		ray->delta_dist_x = 1.0f / camera_x;
	}
	if (ray->ray_dir_y == 0.0f)
		ray->delta_dist_y = INFINITY;
	else
	{
		camera_x = ray->ray_dir_y;
		if (camera_x < 0.0f)
			camera_x = -camera_x;
		ray->delta_dist_y = 1.0f / camera_x;
	}
}

void	init_ray_steps(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0.0f)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - game->player_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0.0f)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - game->player_y)
			* ray->delta_dist_y;
	}
}

static void	step_ray(t_ray *ray, int axis)
{
	if (axis == 0)
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
}

int	perform_dda(t_game *game, t_ray *ray)
{
	int	map_w;
	int	map_h;

	map_w = map_width(game->cfg->map[0]);
	map_h = map_height(game->cfg->map);
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			step_ray(ray, 0);
		else
			step_ray(ray, 1);
		if (ray->map_x < 0 || ray->map_x >= map_w
			|| ray->map_y < 0 || ray->map_y >= map_h)
			return (0);
		if (game->cfg->map[ray->map_y][ray->map_x] == '1'
			|| game->cfg->map[ray->map_y][ray->map_x] == 'D')
			return (1);
	}
}
