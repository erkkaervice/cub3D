/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:55:14 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 18:56:59 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_x(t_game *game, t_ray *ray, float wall_x, int tex_id)
{
	int			tex_x;
	t_texture	*tex;

	if (tex_id < 0 || tex_id >= TEXTURE_COUNT)
		return (0);
	tex = game->textures[tex_id];
	if (!tex || !tex->image)
		return (0);
	tex_x = (int)(wall_x * (float)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

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

float	get_wall_x_with_door(t_game *game, t_ray *ray, float perp_wall_dist)
{
	float	wall_x;
	int		door_idx;
	float	open_ratio;

	if (ray->side == 0)
		wall_x = game->player_y + perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player_x + perp_wall_dist * ray->ray_dir_x;
	wall_x -= floorf(wall_x);

	if (game->cfg->map[ray->map_y][ray->map_x] == 'D')
	{
		door_idx = find_door_index(game, ray->map_x, ray->map_y);
		if (door_idx >= 0)
		{
			open_ratio = game->doors[door_idx].open_ratio;
			if (ray->side == 0)
				wall_x -= open_ratio * ray->step_x;
			else
				wall_x -= open_ratio * ray->step_y;

			if (wall_x < 0.0f)
				wall_x += 1.0f;
			else if (wall_x > 1.0f)
				wall_x -= 1.0f;
		}
	}
	return (wall_x);
}

int	perform_dda(t_game *game, t_ray *ray)
{
	int		map_w;
	int		map_h;
	int		step_count;
	int		max_steps;
	char	tile;
	int		door_idx;
	float	open_ratio;

	map_w = map_width(game->cfg->map[0]);
	map_h = map_height(game->cfg->map);
	step_count = 0;
	max_steps = 1000;
	while (step_count < max_steps)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			step_ray(ray, 0);
		else
			step_ray(ray, 1);
		if (ray->map_x < 0 || ray->map_x >= map_w
			|| ray->map_y < 0 || ray->map_y >= map_h)
			return (0);
		tile = game->cfg->map[ray->map_y][ray->map_x];
		if (tile == '1')
			return (1);
		if (tile == 'D')
		{
			door_idx = find_door_index(game, ray->map_x, ray->map_y);
			if (door_idx >= 0)
			{
				open_ratio = game->doors[door_idx].open_ratio;
				if (open_ratio > 0.0f && open_ratio < 1.0f)
					continue;
				if (open_ratio >= 1.0f)
					continue;
			}
			return (2);
		}
		step_count++;
	}
	return (0);
}
