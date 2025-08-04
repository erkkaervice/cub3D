/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:55:14 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 17:23:34 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_basic(t_game *game, int x, t_ray *ray)
{
	float	camera_x;

	camera_x = 2.0f * x / (float)WIDTH - 1.0f;
	ray->ray_dir_x = game->dir_x + game->plane_x * camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * camera_x;
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	if (ray->ray_dir_x == 0.0f)
		ray->delta_dist_x = 1e30f;
	else
		ray->delta_dist_x = fabsf(1.0f / ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0f)
		ray->delta_dist_y = 1e30f;
	else
		ray->delta_dist_y = fabsf(1.0f / ray->ray_dir_y);
}

static void	init_ray_steps(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0.0f)
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
	if (ray->ray_dir_y < 0.0f)
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

static int	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
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
		if (ray->map_y < 0
			|| ray->map_y >= map_height(game->cfg->map) || ray->map_x < 0
			|| ray->map_x >= map_width(game->cfg->map[0]))
			break ;
		if (game->cfg->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (hit);
}

static void	calculate_wall(t_game *game, t_ray *ray, t_wall *wall)
{
	if (ray->side == 0)
		wall->perp_wall_dist = (ray->map_x - game->player_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		wall->perp_wall_dist = (ray->map_y - game->player_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	wall->line_height = (int)(HEIGHT / wall->perp_wall_dist);
	if (wall->line_height < 1)
		wall->line_height = 1;
	wall->draw_start = -wall->line_height / 2 + HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + HEIGHT / 2;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		wall->tex_x = get_tex_x(game, ray, game->player_y
				+ wall->perp_wall_dist * ray->ray_dir_y);
	else
		wall->tex_x = get_tex_x(game, ray, game->player_x
				+ wall->perp_wall_dist * ray->ray_dir_x);
}

void	raycast(t_game *game)
{
	int		x;
	t_ray	ray;
	t_wall	wall;

	x = 0;
	while (x < WIDTH)
	{
		init_ray_basic(game, x, &ray);
		init_ray_steps(game, &ray);
		if (perform_dda(game, &ray) == 0)
		{
			x++;
			continue ;
		}
		calculate_wall(game, &ray, &wall);
		draw_column(game, x, &wall, &ray);
		x++;
	}
}
