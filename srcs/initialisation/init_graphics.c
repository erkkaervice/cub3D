/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:20:48 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 15:47:22 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(const t_game *g, int x, t_ray *ray)
{
	const float	camera_x = 2.0f * x / (float)g->frame->width - 1.0f;

	ray->ray_dir_x = g->dir_x + g->plane_x * camera_x;
	ray->ray_dir_y = g->dir_y + g->plane_y * camera_x;
	ray->map_x = (int)g->player_x;
	ray->map_y = (int)g->player_y;
	if (ray->ray_dir_x == 0.0f)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = 1.0f / fabsf(ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0f)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = 1.0f / fabsf(ray->ray_dir_y);
}

void	init_ray_steps(const t_game *g, t_ray *ray)
{
	if (ray->ray_dir_x < 0.0f)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->player_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - g->player_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0.0f)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->player_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - g->player_y)
			* ray->delta_dist_y;
	}
}

int	init_mlx(t_game *g)
{
	g->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	if (!g->mlx)
		return (0);
	g->front_buffer = mlx_new_image(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	g->back_buffer = mlx_new_image(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g->front_buffer || !g->back_buffer)
	{
		free(g->front_buffer);
		free(g->back_buffer);
		mlx_terminate(g->mlx);
		return (0);
	}
	if (mlx_image_to_window(g->mlx, g->front_buffer, 0, 0) < 0)
		exit(1);
	g->frame = g->front_buffer;
	g->win_width = WINDOW_WIDTH;
	g->win_height = WINDOW_HEIGHT;
	g->needs_blit = 1;
	mlx_resize_hook(g->mlx, resize_buffers, g);
	return (1);
}
